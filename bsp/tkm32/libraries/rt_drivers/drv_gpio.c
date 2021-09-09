/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-01-07     shelton           first version
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define PIN_NUM(port, no)           (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin)               ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin)                 ((uint8_t)((pin) & 0xFu))

#define PIN_TKMPORTSOURCE(pin)       ((uint8_t)(((pin) & 0xF0u) >> 4))
#define PIN_TKMPINSOURCE(pin)        ((uint8_t)((pin) & 0xFu))
#define PIN_TKMPORT(pin)             ((GPIO_TypeDef *)(GPIOA_BASE + (0x400u * PIN_PORT(pin))))
#define PIN_TKMPIN(pin)              ((uint16_t)(1u << PIN_NO(pin)))
#if defined(GPIOZ)
    #define __TKM32_PORT_MAX 12u
#elif defined(GPIOK)
    #define __TKM32_PORT_MAX 11u
#elif defined(GPIOJ)
    #define __TKM32_PORT_MAX 10u
#elif defined(GPIOI)
    #define __TKM32_PORT_MAX 9u
#elif defined(GPIOH)
    #define __TKM32_PORT_MAX 8u
#elif defined(GPIOG)
    #define __TKM32_PORT_MAX 7u
#elif defined(GPIOF)
    #define __TKM32_PORT_MAX 6u
#elif defined(GPIOE)
    #define __TKM32_PORT_MAX 5u
#elif defined(GPIOD)
    #define __TKM32_PORT_MAX 4u
#elif defined(GPIOC)
    #define __TKM32_PORT_MAX 3u
#elif defined(GPIOB)
    #define __TKM32_PORT_MAX 2u
#elif defined(GPIOA)
    #define __TKM32_PORT_MAX 1u
#else
    #define __TKM32_PORT_MAX 0u
    #error Unsupported TKM32 GPIO peripheral.
#endif
#define PIN_TKMPORT_MAX __TKM32_PORT_MAX

static void _tkm32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    if (PIN_PORT(pin) < PIN_TKMPORT_MAX)
    {
        gpio_port    =  PIN_TKMPORT(pin);
        gpio_pin     =  PIN_TKMPIN(pin);
        GPIO_WriteBit(gpio_port, gpio_pin, (BitAction)value);
    }
}

static int _tkm32_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    int value;

    value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_TKMPORT_MAX)
    {
        gpio_port    =  PIN_TKMPORT(pin);
        gpio_pin     =  PIN_TKMPIN(pin);
        value = GPIO_ReadInputDataBit(gpio_port, gpio_pin);
    }
    return value;
}

static void _tkm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    if (PIN_PORT(pin) < PIN_TKMPORT_MAX)
    {
        gpio_port    =  PIN_TKMPORT(pin);
        gpio_pin     =  PIN_TKMPIN(pin);
    }
    else
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = gpio_pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    }

    GPIO_Init(gpio_port, &GPIO_InitStruct);
}


const static struct rt_pin_ops _tkm32_pin_ops =
{
    _tkm32_pin_mode,
    _tkm32_pin_write,
    _tkm32_pin_read,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
#ifdef GPIOA
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
#endif
#ifdef GPIOB
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
#endif
#ifdef GPIOC
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
#endif
#ifdef GPIOD
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
#endif
#ifdef GPIOE
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
#endif
#ifdef GPIOF
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
#endif
#ifdef GPIOG
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
#endif
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    return rt_device_pin_register("pin", &_tkm32_pin_ops, RT_NULL);
}

INIT_BOARD_EXPORT(rt_hw_pin_init);


#endif /* RT_USING_PIN */
