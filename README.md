# Hart Software Services

This is the Hart Software Services (HSS) code. 

On PIC64GX, this is comprised of two portions:

- A superloop monitor running on the E51 minion processor, which receives requests from the 
   individual U54 application processors to perform certain services on their behalf;

- A Machine-Mode software interrupt trap handler, which allows the E51 to send messages to the U54s, 
   and request them to perform certain functions for it related to rebooting a U54.

The HSS performs boot and system monitoring functions for PIC64GX.

The HSS is compressed (DEFLATE) and stored in eNVM.  On power-up, a small decompressor decompressor wrapper inflates the HSS from eNVM flash to L2-Scratchpad memory and starts the HSS.

## Contributions

Pull requests to this repository must include a per-commit sign-off made by a contributor stating that they agree to the terms published at https://developercertificate.org/ for that particular contribution.

## Source

Source code is found under the `hart-software-services` folder.
   
    hart-software-services
    ├── application (main function, crt startup, init function)
    ├── baremetal
    │   ├── drivers (local modules)
    │   └── pic64gx-bare-metal-library (subtree)
    ├── boards
    │   └── pic64gx-curiosity-kit
    ├── envm-wrapper (helper routines to inflate the HSS to L2-Scratchpad)
    ├── include
    ├── init (system initialization)
    ├── modules
    │   ├── compression
    │   ├── crypto
    │   ├── debug (helper routines for function profiling)
    │   ├── misc (miscellaneous routines)
    │   └── ssmb (secure software message bus)
    │        └── ipi
    ├── services (software service state machines)
    │   ├── beu
    │   ├── boot
    │   ├── crypto
    │   ├── ddr
    │   ├── goto
    │   ├── ipi_poll
    │   ├── mmc
    │   ├── opensbi
    │   ├── powermode
    │   ├── qspi
    │   ├── scrub
    │   ├── sgdma
    │   ├── spi
    │   ├── tinycli
    │   ├── uart
    │   ├── usbdmsc
    │   │    └── flash_drive
    │   ├── wdog
    │   └── ymodem
    └── thirdparty
        ├── Kconfiglib (a Kconfig implementation in Python)
        ├── libecc (library for elliptic curves based cryptography (ECC))
        ├── miniz (fast lossless compression library)
        └── opensbi (RISC-V OpenSBI)

## Building

The build is configured using the Kconfig system of selecting build options. 

The Hart Software Services includes the Kconfig parsing infrastructure directly as a third-party tool invoked by the build system.

Both Linux and Windows are supported by Kconfiglib.
 
The HSS currently support PIC64GX-based Curiosity kit (pic64gx-curiosity-kit) as a board build target.

### Building on Linux

**TBD**

### Building on Windows

**TBD**

### Debug

The `modules/debug/` subdirectory contains code to enable a number of debug features, including:

 * Logging all state machine transitions to the serial console (MMUART0);
 * Periodic logging of super loop timings to the serial console;
 * Logging of IPI statistics to the serial console;
 * Logging all IPI messages for MSC traces;
 * Function profiling.

### Scrubbing for ECCs and Non-Coherent Memory.

The HSS includes a scrubbing service (running on the E51) to scrub ECC protected memories such as DDR, L2 Scratchpad, LIM for correctable single-bit errors in an effort to correct them before they propagate to uncorrectable double-bit errors. Note that by default, mpfs-linux is configured such that DDR accesses to/from peripherals such as PCIe, eNVM and USB are directed to uncached memory addresses; with cache synchronisation performed explicitly by the Linux kerne. Enabling scrubbing can result in interfering with this default mpfs-linux behavior, and so it is important to configure mpfs-linux to only used coherent memory when using scrubbing.

As a consequence, scrubbing is currently off by default in provided `def_config` files.

   # CONFIG_SERVICE_SCRUB is not set
