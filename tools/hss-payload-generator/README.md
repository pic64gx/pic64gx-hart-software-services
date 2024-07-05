% HSS Payload Generator
% 2022-09-02

# Introduction 

This tool creates a formatted payload image for the Hart Software Service zero-stage bootloader on PIC64GX, given a configuration file and a set of ELF binaries.

The configuration file is used to map the ELF binaries or binary blobs to the individual application harts (U54s).

The tool does perform basic sanity checks on the structure of the configuration file itself, and also on the ELF images.  ELF images must be RISC-V executables.

## Example Run

To run this with the sample configuration file and ELF files:

    $ ./hss-payload-generator -c test/config.yaml output.bin

To print diagnostics about a pre-existing image, use `-d`:

    $ ./hss-payload-generator -d output.bin

To enable secure boot authentication (via image signing), use `-p` to specify the location of an X.509 Private Key for the Elliptic Curve P-384 (SECP384r1):

    $ ./hss-payload-generator -c test/config.yaml payload.bin -p /path/to/private.pem

See the documentation on secure boot authentication for more details.

## Config File example

First, we can optionally set a name for our image, otherwise one will be created dynamically:

    set-name: 'PIC64GX-HSS::TestImage'

Next, we'll define the entry point addresses for each hart, as follows:

    hart-entry-points: {u54_1: '0x80200000', u54_2: '0x80200000', u54_3: '0xB0000000', u54_4: '0x80200000'}

The ELF source images can specify an entry point, but we want to be able to support secondary entry points for harts if needed -- i.e., if multiple harts are intended to boot the same image, they might have individual entry points. To support this, we specify the actual entry point addresses in the configuration file itself.

We can now define some payloads (source ELF files, or binary blobs) that will be placed at certain regions in memory.  The payload section is defined with the keyword payloads, and then a number of individual payload descriptors.

Each payload has a name (path to its file), an owner-hart, and optionally 1-3 secondary-harts.

Additionally, it has a privilege mode in which it will start execution.

 * Valid privilege modes are `PRV_M`, `PRV_S` and `PRV_U`, where these are defined as:
     - PRV_M: Machine mode;
     - PRV_S: Supervisor mode;
     - PRV_U: User mode.

In the following example:

 * `test/baremetal.elf` is assumed to be a bare metal application that runs in `U54_3`, and expects to start in `PRV_M`.
 * `test/u-boot-dtb.bin` is the Das U-Boot bootloader application, and it runs on `U54_1`, `U54_2` and `U54_4`.  It expects to start in `PRV_S`.  (Note that the output of U-Boot creates an ELF file, but typically it does not prepend the `.elf` extension. In this case, we are using the binary created by `CONFIG_OF_SEPARATE`, which appends a device tree blob to the U-Boot binary.)
 
    payloads:
      test/baremetal.elf: {exec-addr: '0xB0000000', owner-hart: u54_3, priv-mode: prv_m, skip-opensbi: true}
      test/u-boot-dtb.bin:    {exec-addr: '0x80200000', owner-hart: u54_1, secondary-hart: u54_2, secondary-hart: u54_4, priv-mode: prv_s}

Case only matters for the file path names, not the keywords. So, for instance, `u54_1` is considered the same as `U54_1` and `exec-addr` is considered the same as `EXEC-ADDR`. If an `.elf` or `.bin` extension is present, it needs to be included in the configuration file.

For a bare metal application that doesn't want to be concerned with OpenSBI, the option `skip-opensbi`, if true, will cause the payload on that hart to be invoked using a simple mret rather than an OpenSBI `sbi_init()` call. This means the hart will start running the bare metal code irrespective of any OpenSBI HSM considerations. Note that this also means the hart cannot use `ECALL`s to invoke OpenSBI functionality.  The `skip-opensbi` option is optional, and defaults to false.

To allow a context warm reboot another context, we can add the option `allow-reboot: warm`. To allow a context cold reboot the entire system, we can add the option `allow-reboot: cold`. By default, without specifying `allow-reboot`, a context is only allowed warm reboot itself.

It is also possible to associate ancilliary data with each payload, for example a devicetree blob (DTB) file, by specifying the ancilliary-data filename as follows:

    test/u-boot-icicle-kit-es-2022.01-r0.bin: { exec-addr: '0x80200000', owner-hart: u54_1, secondary-hart: u54_2, secondary-hart: u54_3, secondary-hart: u54_4, priv-mode: prv_s, ancilliary-data: test/icicle-kit-es-microchip.dtb }

This ancilliary data will get included in the payload (placed straight after the main file in executable space), and its address will be passed to OpenSBI in the `next_arg1` field (i.e., passed in the `$a1` register to the image at boot time).

To prevent the HSS from automatically booting a context (for instance, if we instead want to delegate control of this to a context using remoteProc), use the `skip-autoboot` flag.

      test/baremetal.elf: {exec-addr: '0xB0000000', owner-hart: u54_3, priv-mode: prv_m, skip-opensbi: true, skip-autoboot: true}

Finally, we can optionally override the names of individual payloads, using the `payload-name` option. For example:

    test/u-boot-icicle-kit-es-2022.01-r0.bin: { exec-addr: '0x80200000', owner-hart: u54_1, secondary-hart: u54_2, secondary-hart: u54_3, secondary-hart: u54_4, priv-mode: prv_s, ancilliary-data: test/icicle-kit-es-microchip.dtb, payload-name: 'u-boot' }


### Complete Example

Here is the complete example:

    set-name: 'PIC64GX-HSS::AmpTestImage'
    hart-entry-points: {u54_1: '0x80200000', u54_2: '0x80200000', u54_3: '0xB0000000', u54_4: '0x80200000'}
    payloads:
      test/baremetal.elf: {exec-addr: '0xB0000000', owner-hart: u54_3, priv-mode: prv_m, skip-opensbi: true}
      test/u-boot-dtb.bin:    {exec-addr: '0x80200000', owner-hart: u54_1, secondary-hart: u54_2, secondary-hart: u54_4, priv-mode: prv_s, payload-name: 'u-boot-dtb', allow-reboot: warm}

Here is another example, this time of a bare metal SMP application that doesn't require OpenSBI:

    set-name: 'PIC64GX-HSS::SMPBareMetal'
    hart-entry-points: {u54_1: '0x80000000', u54_2: '0x80000000', u54_3: '0x80000000', u54_4: '0x80000000'}
    payloads:
      path/to/smp-baremetal.elf: {exec-addr: '0xB0000000', owner-hart: u54_1, secondary-hart: u54_2, secondary-hart: u54_3, secondary-hart: u54_4, priv-mode: prv_m, skip-opensbi: true, allow-reboot: cold }

## File Structure

````
.
├── crc32.c            // CRC32 calculation routines
├── crc32.h
├── blob_handler.c     // Binary blob file handling
├── blob_handler.h
├── debug_printf.c     // Simple debug Logging routines
├── ebug_printf.h
├── dump_payload.c     // Print diagnostics for payload binary
├── dump_payload.h
├── elf_parser.c       // ELF file processing
├── elf_parser.h
├── elf_strings.c      // Convert ELF enums to strings
├── elf_strings.h
├── generate_payload.c // payload binary output
├── generate_payload.h
├── hss_types.h
├── main.c             // main entry point, command line parsing
├── yaml_parser.c      // YAML configuration file parsing
└── yaml_parser.h

````

# Building the HSS Payload Generator

## Dependencies

This software uses libelf and libyaml, as well as zlib (a dependency of libelf) and libcryto (OpenSSL).

### libelf

libelf provides a shared library which allows reading and writing of ELF files on a high level.

libelf is part of elfutils, a collection of utilities and libraries to read, create and modify ELF binary files, find and handle DWARF debug data, symbols, thread state and stacktraces for processes and core files on GNU/Linux.

**Homepage:** [https://sourceware.org/elfutils/](https://sourceware.org/elfutils/)

### LibYAML

LibYAML is a C library for parsing and emitting data in YAML 1.1, a human-readable data serialization format.

**Homepage:** [http://pyyaml.org/wiki/LibYAML](http://pyyaml.org/wiki/LibYAML)

### zlib

zlib is a library implementing the deflate compression method found in gzip and PKZIP.

**Homepage:** [http://zlib.net/](http://zlib.net/)

### OpenSSL

OpenSSL is a robust, commercial-grade, full-featured toolkit for general-purpose cryptography and secure communication.

**Homepage:** [https://www.openssl.org/](https://www.openssl.org/)

### Installing Dependencies

To install libyaml-dev and libelf-dev in Ubuntu, use:

    $ apt install libyaml-dev libelf-dev zlib1g-dev libssl-dev

To install libyaml and libelf in MSYS2, use:

    $ pacman -S libyaml libyaml-devel libelf libelf-devel zlib zlib-devel openssl-devel

## Verbosity (for Developers Only)

The HSS Payload Generator tool can provide very detailed verbose output for its inner workings. This is typically only of use when modifying or trying to understand the behavior of the HSS Payload Generator itself.

To increase the verbosity, add `-v`.

    $ ./hss-payload-generator -c test/config.yaml -v output.bin

Multiple `-v` arguments increase verbosity level.

    $ ./hss-payload-generator -c test/config.yaml -v -v output.bin
    $ ./hss-payload-generator -c test/config.yaml -v -v -v output.bin

For wide output, use a `-w` argument.

    $ ./hss-payload-generator -c test/config.yaml -v -v -w output.bin

Arguments can also be combined, as follows:

    $ ./hss-payload-generator -vvvwc test/config.yaml output.bin
