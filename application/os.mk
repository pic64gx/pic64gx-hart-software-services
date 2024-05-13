#
# OS Portability Abstraction
#
# Detect if running under:
#   Windows/Command Line
#   Linux/Command Line (Desktop)
#   Linux/Command Line (via console terminal)
#

ifeq ($(OS), Windows_NT)
  $(info INFO: Windows detected)
  HOST_WINDOWS:=true
  PYTHON?=python.exe
else
  SYSTEM:=$(shell uname -s)
  ifneq (, $(findstring Linux, $(SYSTEM)))         # Linux-specific mods
    export PATH:=/usr/bin:$(PATH)
    $(info INFO: Linux detected)
    HOST_LINUX:=true
    PYTHON?=python3
    ifneq ($(origin XDG_SESSION_DESKTOP),undefined)
      HOST_LINUX_DESKTOP:=true
      $(info INFO: Linux Desktop detected)
    endif
  else
    $(error Unsupported build platform $(SYSTEM))
  endif
endif
