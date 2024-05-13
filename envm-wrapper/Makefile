#
# MPFS HSS Embedded Software
#
# Copyright 2019-2021 Microchip Corporation.
#
# SPDX-License-Identifier: MIT
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#
#
# eNVM Compression Wrapper

COMPRESS=tools/compression/hss-deflate.py

OBJS-envm-wrapper = \
	$(BINDIR)/envm-wrapper/envm-wrapper_crt.o \
	$(BINDIR)/envm-wrapper/envm-wrapper_validate_crc.o \
	$(BINDIR)/envm-wrapper/envm-wrapper_stubs.o \
	\
	$(BINDIR)/application/hart0/hss_clock.o \
	$(BINDIR)/init/hss_sys_setup.o \
	$(BINDIR)/modules/misc/hss_crc32.o \
	$(BINDIR)/baremetal/pic64gx-bare-metal-library/src/platform/pic64gx_hal/common/mss_l2_cache.o \
	$(BINDIR)/modules/misc/csr_helper.o \
	$(BINDIR)/modules/misc/assert.o \
	$(BINDIR)/modules/misc/c_stubs.o \
	$(BINDIR)/modules/misc/stack_guard.o \
	$(BINDIR)/thirdparty/miniz/miniz.o \
	$(BINDIR)/modules/misc/uart_helper.o \
        $(BINDIR)/$(BOARD_DIR)/uart_device_list.o \

#ifndef CONFIG_CODE_SIGNING
OBJS-envm-wrapper += \
       $(BINDIR)/baremetal/pic64gx-bare-metal-library/src/platform/pic64gx_hal/common/nwc/mss_nwc_init.o \
       $(BINDIR)/baremetal/pic64gx-bare-metal-library/src/platform/pic64gx_hal/common/nwc/mss_pll.o \
       $(BINDIR)/baremetal/pic64gx-bare-metal-library/src/platform/pic64gx_hal/common/nwc/mss_io.o \
       $(BINDIR)/baremetal/pic64gx-bare-metal-library/src/platform/pic64gx_hal/common/nwc/mss_sgmii.o \
       $(BINDIR)/baremetal/pic64gx-bare-metal-library/src/platform/pic64gx_hal/common/mss_peripherals.o \
       $(BINDIR)/baremetal/pic64gx-bare-metal-library/src/platform/pic64gx_hal/startup_gcc/mss_utils.o \
       $(BINDIR)/baremetal/pic64gx-bare-metal-library/src/platform/drivers/mss/mss_mmuart/mss_uart.o \

#endif


EXTRA_OBJS-envm-wrapper =

LINKER_SCRIPT-envm-wrapper = envm-wrapper/envm-wrapper.ld

COMPRESSED_TARGET=$(BINDIR)/$(TARGET-l2scratch:.elf=.bin.deflate)

$(BINDIR)/envm-wrapper/envm-wrapper_crt.o: $(COMPRESSED_TARGET) 
$(BINDIR)/thirdparty/miniz/miniz.o: CFLAGS=$(CFLAGS_GCCEXT) -DMINIZ_NO_STDIO -DMINIZ_NO_TIME
$(BINDIR)/envm-wrapper/envm-wrapper_validate_crc.o: CFLAGS=$(CFLAGS_GCCEXT)
$(BINDIR)/$(BOARD_DIR)/uart_device_list.o: CFLAGS=$(CFLAGS_GCCEXT)

$(TARGET-envm-wrapper): LIBS:=
$(TARGET-envm-wrapper): $(COMPRESSED_TARGET) $(OBJS-envm-wrapper)
	$(call main-build-target,envm-wrapper)
	@$(ECHO) " BIN       `basename $@ .elf`.bin"
	$(OBJCOPY) -O binary $(BINDIR)/$@ $(BINDIR)/`basename $@ .elf`.bin
	$(SIZE) $(BINDIR)/$(TARGET-envm-wrapper) 2>/dev/null

$(COMPRESSED_TARGET): $(BINDIR)/$(TARGET-l2scratch:.elf=.bin) $(COMPRESS)
	@$(ECHO) " COMPRESS  $<"
	$(PYTHON) $(COMPRESS) $< $@

envm-wrapper_clean:
	-$(RM) $(COMPRESSED_TARGET) $(OBJS-envm-wrapper) $(BINDIR)/$(TARGET-envm-wrapper) $(BINDIR)/`basename $(TARGET-envm-wrapper) .elf`.sym $(BINDIR)/`basename $(TARGET-envm-wrapper) .elf`.bin

program:
	riscv-none-elf-gdb --command=tools/gdbscripts/program.gdb
