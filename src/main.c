#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <hardware/adc.h>

#include "template.h"
#include "lwipopts.h"

#define TEMP_ADC 4

const float conversion_factor = 3.3f / (1 << 12);

int main()
{
    if (!stdio_init_all())
    {
        printf("Stdio init failed");
        return STDIO_INIT_FAILURE;
    }

    gpio_init(CYW43_WL_GPIO_LED_PIN);
    gpio_set_dir(CYW43_WL_GPIO_LED_PIN, GPIO_OUT);
    gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

    adc_init();
    adc_gpio_init(26);
    adc_set_temp_sensor_enabled(true);

    adc_select_input(TEMP_ADC);

    while (true)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(1000);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(1000);

        const float voltage = adc_read() * conversion_factor;
        const float temperature = 27 - (voltage - 0.706) / 0.001721;

        printf("Hello, world! The temperature is: %fc\n", temperature);
    }
}
