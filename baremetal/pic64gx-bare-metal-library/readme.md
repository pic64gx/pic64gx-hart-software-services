# PIC64GX Bare Metal Library
This folder contains the PIC64GX Bare Metal Library.

The PIC64GX Bare Metal Library includes:
- Source code for start-up code and Hardware Abstraction Layer (HAL) for the PIC64GX RISC-V processor complex
- Source code for the PIC64GX Coreplex Subsystem (Coreplex) peripheral drivers
- Documentation for the HAL and peripheral drivers

## Source
Source code is found under the "src" folder.

    pic64gx-bare-metal-library
        |
        |--- docs
        |--- examples
        |--- src
              |--- platform
                    |--- config
                    |       |--- hardware
                    |       |--- linker
                    |       |--- software
                    |
                    |--- drivers
                    |--- hal
                    |--- mpfs_hal
                    
### src/platform
The src/platform folder contains the entire source code specific to PIC64GX. 

#### src/platform/drivers
The src/platform/drivers folder contains the source code for the Coreplex peripherals and DirectCore soft IP. The content of this folder is not intended to be modified.

#### src/platform/hal
The src/platform/hal folder contains the Hardware Abstraction Layer (HAL). This part of the HAL is intended to be generic across all SoC-FPGA devices.
It is mainly used by DirectCore FPGA IP cores' drivers. The content of this folder is not intended to be modified.

#### src/platform/mpfs_hal
The src/platform/mpfs_hal folder contains the part of the HAL specific to PIC64GX. It contains start-up code and Coreplex peripheral register descriptions.
The content of this folder is not intended to be modified.
