#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/uart.h"
#include "movement.h"
#include "defs.h"
#include "udp.h"
#include <string>

struct udp_pcb *udp_server;

int main()
{
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    std::string SSID = "SSID";
    std::string PASSWORD = "PASS";

    UDPModule net(SSID.data(), PASSWORD.data());
 
    while (true) 
    {
        printf("Running!\n");
        cyw43_arch_gpio_put(LED_PIN, 1); 
        sleep_ms(LED_DELAY_MS - 100);
        cyw43_arch_gpio_put(LED_PIN, 0);
        sleep_ms(LED_DELAY_MS - 100);
    }
}

