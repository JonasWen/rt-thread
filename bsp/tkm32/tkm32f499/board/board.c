/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     Jonas        first version
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>

#include <tkm32f499.h>
#include <board.h>

#ifdef BSP_USING_SRAM
#include "drv_sram.h"
#endif

RT_WEAK void rt_hw_us_delay(rt_uint32_t us)
{
    
}

#ifdef RT_USING_FINSH
#include <finsh.h>
static void reboot(uint8_t argc, char **argv)
{
    rt_hw_cpu_reset();
}
FINSH_FUNCTION_EXPORT_ALIAS(reboot, __cmd_reboot, Reboot System);
#endif /* RT_USING_FINSH */

/** System Clock Configuration
*/
void SystemClock_Config(void)
{
    extern uint32_t SystemCoreClock;
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    NVIC_SetPriority(SysTick_IRQn, 0);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}
void SysClk_Init(void)
{
    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    while(1)
    {
        if(RCC_WaitForHSEStartUp() != 0)
        {
            break;
        }
    }
    RCC_PLLCmd(DISABLE);
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_20);
    RCC_PLLCmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}

void RemapVtorTable(void)
{
#define VECT_TAB_OFFSET 0
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_SRAM, ENABLE);//bkp clk,enable sram
    //关ROM区中断
    for (int i = 0; i < sizeof(IRQn_Type); i++)
    {
        NVIC_DisableIRQ((IRQn_Type)i);
    }
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET;
    rt_memcpy((void *)T_SRAM_BASE, (void *)T_SDRAM_BASE, 512);
}

/**
 * This function will initial TKM32 board.
 */
void rt_hw_board_init()
{
    RemapVtorTable();
    SysClk_Init();
    SystemClock_Config();

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef BSP_USING_SRAM
    rt_system_heap_init((void *)EXT_SRAM_BEGIN, (void *)EXT_SRAM_END);
#else
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
}
