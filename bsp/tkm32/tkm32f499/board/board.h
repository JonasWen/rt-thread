/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-15     shelton      first version
 * 2021-02-09     shelton      add flash macros
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <tkm32f499.h>
#include "tkm32_msp.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Just only support for AT32F40xxG */
#define AT32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define FLASH_PAGE_SIZE             (2 * 1024)
#define AT32_FLASH_SIZE             (1024 * 1024)
#define AT32_FLASH_END_ADDRESS      ((uint32_t)(AT32_FLASH_START_ADRESS + AT32_FLASH_SIZE))

/* Internal SRAM memory size[Kbytes] <96>, Default: 96*/
#define TKM32_SDRAM_BASE            (0x70020000)
#define TKM32_SDRAM_USE_FOR_ROM     (0x200000)
#define TKM32_SRAM_BASE             (TKM32_SDRAM_BASE + TKM32_SDRAM_USE_FOR_ROM)
#define TKM32_SRAM_SIZE             (6000)
#define TKM32_SRAM_END              (TKM32_SRAM_BASE + TKM32_SRAM_SIZE * 1024)

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      ((void *)&__bss_end)
#endif

#define HEAP_END        TKM32_SRAM_END

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
