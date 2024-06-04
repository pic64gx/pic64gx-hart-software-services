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
# Defines Rules such as compiler and tool choice/settings, build flags, and
# basic build rules (.c to .o, etc)
#

CROSS_COMPILE?=riscv64-unknown-elf-
#CROSS_COMPILE?=riscv-none-elf-
CC=$(CROSS_COMPILE)gcc
RANLIB=$(CROSS_COMPILE)ranlib
CPP=$(CROSS_COMPILE)cpp
LD=$(CROSS_COMPILE)ld
SIZE=$(CROSS_COMPILE)size
GPROF=$(CROSS_COMPILE)gprof
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump
READELF=$(CROSS_COMPILE)readelf
NM=$(CROSS_COMPILE)nm
ECHO=echo
MAKE=make
CP=cp
MAKEDEP=makedepend
GENCONFIG:=thirdparty/Kconfiglib/genconfig.py
MENUCONFIG:=thirdparty/Kconfiglib/menuconfig.py
GUICONFIG:=thirdparty/Kconfiglib/guiconfig.py

#
#
PLATFORM_RISCV_ABI=lp64
#PLATFORM_RISCV_ISA=rv64imac_zicsr_zifencei
PLATFORM_RISCV_ISA=rv64imac

CORE_CFLAGS+=$(MCMODEL) -mstrict-align

CORE_CFLAGS+=-mabi=$(PLATFORM_RISCV_ABI) -march=$(PLATFORM_RISCV_ISA)

# Debug options
CORE_CFLAGS+=-g3 -DDEBUG -pipe -grecord-gcc-switches
#CORE_CFLAGS+=-pipe

VENDOR_STRING=$(shell git describe --tags 2> /dev/null || echo "unknown")
CORE_CFLAGS+=-DVENDOR_STRING="$(VENDOR_STRING)"

# Warning / Code Quality
CORE_CFLAGS+=-Wall -Werror -Wshadow -fno-builtin -fno-builtin-printf \
   -fomit-frame-pointer -Wredundant-decls -Wall -Wundef -Wwrite-strings -fno-strict-aliasing \
   -fno-common -Wendif-labels -Wmissing-include-dirs -Wempty-body -Wformat=2 -Wformat-security \
   -Wformat-y2k -Winit-self -Wignored-qualifiers -Wold-style-declaration -Wold-style-definition \
   -Wtype-limits -Wstrict-prototypes -Wimplicit-fallthrough=5

CORE_CFLAGS+=-mno-fdiv
# CORE_CFLAGS+=-fanalyzer

# Compiler hooks to enable link-time garbage collection
CORE_CFLAGS+=-ffunction-sections -fdata-sections

# Stack Usage
ifdef CONFIG_CC_DUMP_STACKSIZE
CORE_CFLAGS+=-fstack-usage
endif

#-ffreestanding

# TODO - introduce the following prototype warnings...
CORE_CFLAGS+=-Wmissing-prototypes
# TODO - introduce the following conversion warnings... Currently fails on drivers and OpenSBI
#CORE_CFLAGS+=-Wconversion
# TODO - introduce trapv for integer overflows etc... Currently missing primitives
#CORE_CFLAGS+=-ftrapv

CFLAGS=-std=c11 $(CORE_CFLAGS) $(PLATFORM_CFLAGS) -Wmissing-prototypes

# separate flags for C files that need GCC Extensions...
CFLAGS_GCCEXT=$(CORE_CFLAGS) $(PLATFORM_CFLAGS)
#OPT-y=-O2
#OPT-y+=-Os -funroll-loops -fpeel-loops -fgcse-sm -fgcse-las
OPT-y+=-Os -fno-strict-aliasing -fwhole-program -Wno-lto-type-mismatch
#OPT-y+=-Os -fno-strict-aliasing

ifndef CONFIG_LD_RELAX
OPT-y+=-Wl,--no-relax
endif

#
# for some reason, -flto isn't playing nicely currently with -fstack-protector-strong...
# Stack protection is really useful, but if it is enabled, for now disabling LTO optimisation
#
ifdef CONFIG_CC_STACKPROTECTOR_STRONG
  $(info INFO: Not enabling -flto as stack protector enabled)
  CORE_CFLAGS+=-fstack-protector-strong
  # CORE_CFLAGS+=-fstack-clash-protection  # currently does nothing on RISC-V
else
  $(info INFO: NOTICE: enabling -flto (which means stack protection is disabled))
  OPT-y+=-flto=auto -ffat-lto-objects -fno-stack-protector
endif


##############################################################################
#
# Sanity Checks
#
# is compile toolchain what we are expecting?

ifeq ($(HOST_LINUX), true)
  ifeq ($, $(shell which $(CC)))
    $(error "No $(CC) in $(PATH)")
  endif
  CC_VERSION = $(strip $(shell $(CC) -dumpversion))
  EXPECTED_CC_VERSION := 8.3.0
  ifneq ($(CC_VERSION),$(EXPECTED_CC_VERSION))
    $(info INFO: Expected $(CC) version $(EXPECTED_CC_VERSION) but found $(CC_VERSION))
  endif

  CC_MACHINE = $(strip $(shell $(CC) -dumpmachine))
  EXPECTED_CC_MACHINE := riscv64-unknown-elf
  ifneq ($(CC_MACHINE),$(EXPECTED_CC_MACHINE))
    $(info INFO: Expected $(CC) version $(EXPECTED_CC_MACHINE) but found $(CC_MACHINE))
  endif
endif

##############################################################################
#
# Build Rules
#

ifeq ($(V), 1)
else
.SILENT:
endif

OBJS = $(addprefix $(BINDIR)/,$(SRCS-y:.c=.o))
EXTRA_OBJS += $(addprefix $(BINDIR)/,$(EXTRA_SRCS-y:.c=.o))
EXTRA_OBJS += $(addprefix $(BINDIR)/,$(ASM_SRCS:.S=.o))
EXTRA_OBJS += $(addprefix $(BINDIR)/,$(EXTRA_OBJS-y))
EXTRA_OBJS += $(addprefix $(BINDIR)/,$(ASM_SRCS-y:.S=.o))

.SUFFIXES:

%.s: %.c $(CONFIG_H)
	$(ECHO) " CC -s     $@"
	$(CC) $(CFLAGS_GCCEXT) $(OPT-y) $(INCLUDES) -c -S -g  $<  -o $@

%.S: %.c $($(CONFIG_H)
	$(ECHO) " CC -S     $@"
	$(CC) $(CFLAGS_GCCEXT) $(OPT-y) $(INCLUDES) -c -Wa,-adhln -g  $<  > $@

%.e: %.c $($(CONFIG_H)
	$(ECHO) " CC -E     $@"
	$(CC) $(CFLAGS_GCCEXT) $(OPT-y) $(INCLUDES) -c -E -o $@ $<

%.e: %.s $($(CONFIG_H)
	$(ECHO) " CC -E     $@"
	$(CC) $(CFLAGS_GCCEXT) $(OPT-y) $(INCLUDES) -c -E -o $@ $<

ifdef CONFIG_CC_USE_MAKEDEP
  $(BINDIR)/%.o: %.c $(CONFIG_H) $(BINDIR)/%.d
else
  $(BINDIR)/%.o: %.c $(CONFIG_H)
endif
	if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(ECHO) " CC        $@"
	$(CC) $(CFLAGS) $(OPT-y) $(INCLUDES) -c -o $@ $<

%.o: %.c $(CONFIG_H)
	$(ECHO) " CC        $@"
	$(CC) $(CFLAGS) $(OPT-y) $(INCLUDES) -c -o $@ $<

$(BINDIR)/%.o: %.S $(CONFIG_H)
	if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(ECHO) " CC        $@"
	$(CC) $(CFLAGS) $(OPT-y) $(INCLUDES) -D__ASSEMBLY__=1 -c -o $@ $<

#%.hex: %.elf
#	$(ECHO) " HEX       $@"
#	$(OBJCOPY) -O ihex $< $@
#	$(OBJCOPY) -O ihex $< Default/$@

%.lss: %.elf
	$(ECHO) " LSS       $@"
	$(OBJDUMP) -h -S -z $< > $@

%.sym: %.elf
	$(ECHO) " NM        $@"
	$(NM) -n $< > $@

%.bin: %.elf
	$(ECHO) " BIN       $@"
	$(OBJCOPY) -O binary $< $@

%.ld: %.lds $(CONFIG_H)
	$(ECHO) " CPP       $@"
	$(CPP) -P $(INCLUDES) $< -o $@

#
$(BINDIR)/%.d: %.c
	if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(MAKEDEP) -f - $(INCLUDES) $< 2>/dev/null | sed 's,\($*\.o\)[ :]*\(.*\),$@ : $$\(wildcard \2\)\n\1 : \2,g' > $(BINDIR)/$*.d

$(BINDIR)/%.d: %.S
	if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(MAKEDEP) -f - $(INCLUDES) $< 2>/dev/null | sed 's,\($*\.o\)[ :]*\(.*\),$@ : $$\(wildcard \2\)\n\1 : \2,g' > $(BINDIR)/$*.d
