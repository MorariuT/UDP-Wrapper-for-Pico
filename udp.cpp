#include "udp.h"

UDPModule::UDPModule(char* SSID, char* PASSWORD)
{
    if (cyw43_arch_init()) 
    {
        printf("Wi-Fi init failed\n");
        return;
    }

    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(SSID, PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000))
    {
        
        printf("failed to connect.\n");
        while (true)
        {
            cyw43_arch_gpio_put(LED_PIN, 1); 
            sleep_ms(LED_DELAY_MS);
            cyw43_arch_gpio_put(LED_PIN, 0);
            sleep_ms(LED_DELAY_MS);
        }
        return;
    } 
    else 
    {
        connected = true;
        cyw43_arch_gpio_put(LED_PIN, 1); 
        printf("Connected.\n");
    }
}

void UDPModule::init_udp(uint16_t port)
{
    if(!connected)
    {
        printf("Not connected to WiFi\n");
        return;
    }
    udp_initialized = true;
    udp_server = udp_new();
    udp_bind(udp_server, IP_ADDR_ANY, port);
    udp_recv(udp_server, udp_receive_callback, NULL);
}

void UDPModule::send_udp(char* message, ip_addr_t dest_ip, uint16_t port)
{
    if(!udp_initialized)
    {
        printf("UDP not initialized\n");
        return;
    }
    if(!connected)
    {
        printf("Not connected to WiFi\n");
        return;
    }
    struct pbuf *p;
    p = pbuf_alloc(PBUF_TRANSPORT, strlen(message), PBUF_RAM);
    memcpy(p->payload, message, strlen(message));
    udp_sendto(udp_server, p, &dest_ip, port);
    pbuf_free(p);
}

void UDPModule::udp_receive_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port) 
{
    if (p != NULL) 
    {
        char buffer[p->tot_len + 1];
        memcpy(buffer, p->payload, p->tot_len);
        buffer[p->tot_len] = '\0'; 

        printf("Received UDP packet from %s:%d - %s\n", ipaddr_ntoa(addr), port, buffer);
        fflush(stdout); 

        
        pbuf_free(p); 
    }
}