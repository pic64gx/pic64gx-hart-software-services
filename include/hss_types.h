#ifndef HSS_TYPES_H
#define HSS_TYPES_H

/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 *
 * Hart Software Services - HSS Types
 *
 */

/**
 * \file PIC64GX HSS Embedded Software - Types
 * \brief PIC64GX HSS Embedded Software - Types
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>     // ptrdiff_t
/*
 * We'll use the same trick as used by Linux for its Kconfig options...
 *
 * With variable arguments to our macro, if our config option is defined, it will cause
 * the insertion of "0, " as a prefix the arguments to ___IS_ENABLED(CONFIG_), which will
 * then cause __IS_ENABLED(CONFIG_) itself to resolve to 1, otherwise 0
 *
 */
#define _ARG_SHUFFLE_RIGHT_IF_1                 0,
#define IS_ENABLED(cfg)                         _IS_ENABLED(cfg)
#define _IS_ENABLED(val)                        __IS_ENABLED(_ARG_SHUFFLE_RIGHT_IF_##val)
#define __IS_ENABLED(shuffle_or_blank)          ___IS_ENABLED(shuffle_or_blank 1, 0)
#define ___IS_ENABLED(ignored, desiredVal, ...) desiredVal

#define ARRAY_SIZE(x)		(sizeof(x)/sizeof(x[0]))

#define mHSS_BOOT_MAGIC		(0xB007C0DEu)
#define mHSS_COMPRESSED_MAGIC	(0xC08B8355u)

#define mHSS_BOOT_VERSION       1u

#ifndef CONFIG_OPENSBI
#  ifndef MIN
#    define MIN(A,B)		((A) < (B) ? A : B)
#  endif
#  define likely(x)		__builtin_expect((x), 1)
#  define unlikely(x)		__builtin_expect((x), 0)
#  ifndef __ssize_t_defined
#    define __ssize_t_defined
       typedef long			ssize_t;
#  endif
#  include <sys/types.h>  // for size_t
#  include <stdbool.h> // for bool, true, false
#  include <stdint.h>
#else
#  ifdef __packed
#    undef __packed
#  endif
#  include "sbi/sbi_types.h"
#  define true TRUE
#  define false FALSE
#endif

/**
 * \brief HSS Cores Enumeration
 */
enum HSSHartId {
    HSS_HART_E51 = 0,
    HSS_HART_U54_1,
    HSS_HART_U54_2,
    HSS_HART_U54_3,
    HSS_HART_U54_4,

    HSS_HART_NUM_PEERS,
    HSS_HART_ALL = HSS_HART_NUM_PEERS
};
#define MAX_NUM_HARTS ((unsigned)HSS_HART_NUM_PEERS)
#define mHSS_BITMASK_ALL_U54 (0x1Eu)

#define BOOT_FLAG_ANCILLIARY_DATA      (0x80u)
#define BOOT_FLAG_SKIP_OPENSBI         (0x40u)
#define BOOT_FLAG_ALLOW_COLD_REBOOT    (0x20u)
#define BOOT_FLAG_ALLOW_WARM_REBOOT    (0x10u)
#define BOOT_FLAG_SKIP_AUTOBOOT        (0x08u)

typedef union HSSHartBitmask {
    unsigned int uint;
    struct {
       unsigned int e51:1;
       unsigned int u54_1:1;
       unsigned int u54_2:1;
       unsigned int u54_3:1;
       unsigned int u54_4:1;
    } s;
} HSSHartBitmask_t;



/**
 * \brief Chunk Descriptor Structure for boot image
 *
 * Describes where to copy and how much...
 *
 */
#pragma pack(8)
struct HSS_BootChunkDesc {
    enum HSSHartId owner;
    uintptr_t loadAddr;
    uintptr_t execAddr;
    size_t size;
    uint32_t crc32;
};


/**
 *  * \brief Descriptor for U54 Boot Zero-Initialized Chunk
 *   */
struct HSS_BootZIChunkDesc {
    enum HSSHartId owner;
    void *execAddr;
    size_t size;
};

/**
 * \brief Boot Image Structure
 *
 * \warning The chunk table *must* be terminated with a size of 0 sentinel!
 */
#define BOOT_IMAGE_MAX_NAME_LEN (256)

// pre crypto-signing, the BootImage format was slightly different, so to ensure
// no CRC failures on older images, we provide a legacy structure here purely for sizing
struct HSS_BootImage_v0 {
    uint32_t magic;
    uint32_t version;
    size_t headerLength;
    uint32_t headerCrc;
    size_t chunkTableOffset;
    size_t ziChunkTableOffset;
    struct {
        uintptr_t entryPoint;
        uint8_t privMode;
        uint8_t flags;
        size_t numChunks;
        size_t firstChunk;
        size_t lastChunk;
        char name[BOOT_IMAGE_MAX_NAME_LEN];
    } hart[MAX_NUM_HARTS-1]; // E51 is not counted, only U54s
    char set_name[BOOT_IMAGE_MAX_NAME_LEN];
    size_t bootImageLength;
    uint8_t pad1[32];
    uint8_t pad2[32];
};

struct HSS_Signature {
    uint8_t digest[48];     // SHA384
    uint8_t ecdsaSig[96]; // SECP384R1
};

struct HSS_BootImage {
    uint32_t magic;
    uint32_t version;
    size_t headerLength;
    uint32_t headerCrc;
    size_t chunkTableOffset;
    size_t ziChunkTableOffset;
    struct {
        uintptr_t entryPoint;
        uint8_t privMode;
        uint8_t flags;
        size_t numChunks;
        size_t firstChunk;
        size_t lastChunk;
        char name[BOOT_IMAGE_MAX_NAME_LEN];
    } hart[MAX_NUM_HARTS-1]; // E51 is not counted, only U54s
    char set_name[BOOT_IMAGE_MAX_NAME_LEN];
    size_t bootImageLength;
    struct HSS_Signature signature;
};


/**
 * \brief Compressed Image Structure
 *
 */
struct HSS_CompressedImage {
    uint32_t magic;
    uint32_t version;
    size_t headerLength;
    uint32_t headerCrc;
    uint32_t compressedCrc;
    uint32_t originalCrc;
    size_t compressedImageLen;
    size_t originalImageLen;
#if IS_ENABLED(CONFIG_CRYPTO_SIGNING)
    struct HSS_Signature signature;
#else
    uint8_t pad1[32]; // padding to keep compatibility with older format
    uint8_t pad2[32]; // padding to keep compatibility with older format
#endif
};

struct HSS_Storage;
typedef bool (* HSS_GetBootImageFnPtr_t)(struct HSS_Storage *pStorage, struct HSS_BootImage **ppBootImage);
struct HSS_Storage {
    char const * const name;
    HSS_GetBootImageFnPtr_t const getBootImage;
    bool (* const init)(void);
    bool (* const readBlock)(void *pDest, size_t srcOffset, size_t byteCount);
    bool (* const writeBlock)(size_t dstOffset, void *pSrc, size_t byteCount);
    void (* const getInfo)(uint32_t *pBlockSize, uint32_t *pEraseSize, uint32_t *pBlockCount);
    void (* const flushWriteBuffer)(void);
};

#define mHSS_COMPRESSED_VERSION_DEFLATE  1u


#ifdef __cplusplus
}
#endif

#endif
