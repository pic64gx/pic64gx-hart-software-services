# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## 2026.10

### Added
 * HSS: feat(suspend): add SBI_EXT_SUSP system suspend/resume support
 * HSS: feat(suspend): add WFI, and store source hart
 * Bare Metal Library: feat(mss_i2c): add non-blocking poll API

### Changed
 * HSS: refactor(beu): on double-bit error, reboot hart
 * HSS: refactor(envm-wrapper): safety checks, auto-generated struct offsets and decompression guards
 * HSS: refactor(gpt): improve GPT validation
 * HSS: refactor(ymodem): fix several issues (WDOG, QSPI, overflows)
 * HSS: refactor(uart): remove unused UART service
 * HSS: fix(hss): update overall version number to 0.99.53
 * Payload Generator: fix(payload-gen): update version number to 0.99.53

### Fixed
 * Bare Metal Library: fix(mss_util): fix sleep_ms() tick calculation
 * HSS: fix(curiosity): use mac0 in minimal device tree, matching Linux and U-Boot
 * HSS: fix(boot): fix erroneous boot messages about DDR
 * HSS: fix(boot): validate U-mode pointers in ecall paths
 * HSS: fix(boot): improve checks for various error conditions
 * HSS: fix(boot): restore exact-size chunk copy and fix PDMA/memcpy split
 * HSS: fix(goto): flush I$ on target hart before GOTO
 * HSS: fix(opensbi): register MC callback for IHC channels
 * HSS: fix(opensbi): prevent PLIC reset during Linux boot
 * HSS: fix(opensbi): mismatch in domain memory region order
 * HSS: fix(sbi): masquerade as SBI 2.0 to add SUSP ecall
 * HSS: fix(crt.s): sp computed before hartid bounds check
 * HSS: fix(storage): various truncation issues resolved
 * HSS: fix(storage): missing check for NULL writeBlock
 * HSS: fix(qspi): improve QSPI bounds checks
 * HSS: fix(platform): correctly re-enable IPIs
 * HSS: fix(ddr): correct number of states
 * HSS: fix(tinycli): RESUME post-boot command warning
 * HSS: fix(tinycli): monitors > 0 timestamps not updated
 * HSS: fix(uart): use UART assigned to current hart
 * HSS: fix(mss_sgmii): clock/reset configures MAC0 twice
 * Payload Generator: fix(hss-payload-gen): avoid corruption on Windows
 * Payload Generator: fix(payload-gen): remove duplicated copyright and version lines

## 2026.04

### Added
 * HSS: feat(boot): allow null AMP payload (for harts that need no initial image)
 * Payload Generator: feat(hss-payload-gen): add null payload support

 ### Changed
 * HSS: bump OpenOCD version referenced in the README
 * HSS: clarify programming instructions in the README

 ### Fixed
 * HSS: workaround for voltage select issue

## 2024.05

### Added
 * HSS: initial version for PIC64GX-Curiosity-Kit
