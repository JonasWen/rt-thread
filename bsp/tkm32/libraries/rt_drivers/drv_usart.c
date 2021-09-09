/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-15     Jonas        first version
 */

#include <board.h>
#include "drv_usart.h"

#ifdef RT_USING_SERIAL
#if !defined(BSP_USING_UART1)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig → RT-Thread Components → Device Drivers */
#endif

struct tkm32_uart
{
    char *name;
    UART_TypeDef *uartx;
    IRQn_Type irqn;
    struct rt_serial_device serial;
};

enum
{
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
};

static struct tkm32_uart uart_config[] =
{
#ifdef BSP_USING_UART1
    {
        "uart1",
        UART1,
        UART1_IRQn,
    },
#endif
#ifdef BSP_USING_UART2
    {
        "uart2",
        USART2,
        USART2_IRQn,
    },
#endif
};

static rt_err_t tkm32_configure(struct rt_serial_device *serial,
                               struct serial_configure *cfg)
{
    struct tkm32_uart *uart_instance = (struct tkm32_uart *) serial->parent.user_data;
    UART_InitTypeDef UART_InitStructure;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    RT_ASSERT(uart_instance != RT_NULL);

    tkm32_msp_usart_init((void *)uart_instance->uartx);

    UART_StructInit(&UART_InitStructure);

    UART_DeInit(uart_instance->uartx);
    UART_InitStructure.UART_BaudRate = cfg->baud_rate;
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
    UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        UART_InitStructure.UART_WordLength = UART_WordLength_8b;
        break;

    case DATA_BITS_9:
        //UART_InitStructure.UART_WordLength = UART_WordLength_9b;
        UART_InitStructure.UART_WordLength = UART_WordLength_8b;
        break;
    default:
        UART_InitStructure.UART_WordLength = UART_WordLength_8b;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        UART_InitStructure.UART_StopBits = UART_StopBits_1;
        break;
    case STOP_BITS_2:
        UART_InitStructure.UART_StopBits = UART_StopBits_2;
        break;
    default:
        UART_InitStructure.UART_StopBits = UART_StopBits_1;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        UART_InitStructure.UART_Parity = UART_Parity_No;
        break;
    case PARITY_ODD:
        UART_InitStructure.UART_Parity = UART_Parity_Odd;
        break;
    case PARITY_EVEN:
        UART_InitStructure.UART_Parity = UART_Parity_Even;
        break;
    default:
        UART_InitStructure.UART_Parity = UART_Parity_No;
        break;
    }
    UART_Init(uart_instance->uartx, &UART_InitStructure);
    UART_Cmd(uart_instance->uartx, ENABLE);

    return RT_EOK;
}

static rt_err_t tkm32_control(struct rt_serial_device *serial, int cmd,
                             void *arg)
{
    struct tkm32_uart *uart;

    NVIC_InitTypeDef NVIC_InitStruct;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct tkm32_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    NVIC_InitStruct.NVIC_IRQChannel = uart->irqn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&NVIC_InitStruct);
        UART_ITConfig(uart->uartx, UART_IT_RXIEN, DISABLE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStruct);
        UART_ITConfig(uart->uartx, UART_IT_RXIEN, ENABLE);
        break;
    }

    return RT_EOK;
}

static int tkm32_putc(struct rt_serial_device *serial, char ch)
{
    struct tkm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct tkm32_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    UART_SendData(uart->uartx, (uint8_t) ch);
    while (UART_GetFlagStatus(uart->uartx, UART_FLAG_TXEMPTY) == RESET);

    return 1;
}

static int tkm32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct tkm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct tkm32_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    ch = -1;
    if (RESET != UART_GetFlagStatus(uart->uartx, UART_FLAG_RXAVL))
    {
        ch = UART_ReceiveData(uart->uartx) & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops tkm32_usart_ops =
{
    tkm32_configure,
    tkm32_control,
    tkm32_putc,
    tkm32_getc,
    RT_NULL
};

static void usart_isr(struct rt_serial_device *serial)
{
    struct tkm32_uart *uart_instance;

    RT_ASSERT(serial != RT_NULL);

    uart_instance = (struct tkm32_uart *) serial->parent.user_data;
    RT_ASSERT(uart_instance != RT_NULL);

    if ((UART_GetITStatus(uart_instance->uartx, UART_IT_RXIEN) != RESET) \
            && (RESET != UART_GetFlagStatus(uart_instance->uartx, UART_FLAG_RXAVL)))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        UART_ClearITPendingBit(uart_instance->uartx, UART_IT_RXIEN);
        UART_ClearFlag(uart_instance->uartx, UART_FLAG_RXAVL);
    }
    else
    {
        if (UART_GetFlagStatus(uart_instance->uartx, UART_FLAG_TXEPT) != RESET)
        {
            UART_ClearFlag(uart_instance->uartx, UART_FLAG_TXEPT);
        }
    }
}

#ifdef BSP_USING_UART1
void UART1_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&uart_config[UART1_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART2
void USART2_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&usart_config[USART2_INDEX].serial);

    rt_interrupt_leave();
}
#endif

int rt_hw_usart_init(void)
{
    rt_size_t obj_num;
    int index;

    obj_num = sizeof(uart_config) / sizeof(struct tkm32_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++)
    {
        uart_config[index].serial.ops = &tkm32_usart_ops;
        uart_config[index].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&uart_config[index].serial,
                                       uart_config[index].name,
                                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX, &uart_config[index]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_usart_init);

#endif /* BSP_USING_SERIAL */
