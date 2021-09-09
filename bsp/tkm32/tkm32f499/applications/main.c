
#include <rtthread.h>
#include <drv_gpio.h>
#define LED_PIN     GET_PIN(D,  8)

int main(void)
{
    int cnt = 1;
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
    while(cnt++)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
