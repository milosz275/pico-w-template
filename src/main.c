#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <pico/multicore.h>
#include <hardware/adc.h>

#include "template.h"
#include "lwipopts.h"
#include "wifi_credentials.h"

#define TEMPERATURE_UNITS 'C'

/* 12-bit conversion, assume max value == ADC_VREF == 3.3 V */
const float conversion_factor = 3.3f / (1 << 12);

float read_onboard_temperature(const char unit)
{
    float adc = (float)adc_read() * conversion_factor;
    float temp_c = 27.0f - (adc - 0.706f) / 0.001721f;

    if (unit == 'C')
        return temp_c;
    else if (unit == 'F')
        return temp_c * 9 / 5 + 32;
    else if (unit == 'K')
        return temp_c + 273.15f;

    return -1.0f;
}

void print_temperature()
{
    while (true)
    {
        float temperature = read_onboard_temperature(TEMPERATURE_UNITS);
        printf("Onboard temperature = %.02f %c\n", temperature, TEMPERATURE_UNITS);
        sleep_ms(1000);
    }
}

int main()
{
    // init
    stdio_init_all();
    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed");
        return -1;
    }

    // adc init
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    // wifi init
    cyw43_arch_enable_sta_mode();
    cyw43_wifi_pm(&cyw43_state, cyw43_pm_value(CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1));

    printf("Connecting to WiFi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000))
    {
        printf("failed to connect.\n");
        return 1;
    }
    else
    {
        printf("Connected.\n");
        extern cyw43_t cyw43_state;
        uint32_t ip_addr = cyw43_state.netif[CYW43_ITF_STA].ip_addr.addr;
        printf("IP Address: %lu.%lu.%lu.%lu\n", ip_addr & 0xFF, (ip_addr >> 8) & 0xFF, (ip_addr >> 16) & 0xFF, ip_addr >> 24);
    }

    // main loop
    multicore_launch_core1(print_temperature);
    while (true)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);
    }
}
