#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/uart.h"
#include "defs.h"

class UDPModule
{
    public:
        struct udp_pcb *udp_server;
        UDPModule(char* SSID, char* PASSWORD);
        void init_udp(uint16_t port);
        void send_udp(char* message, ip_addr_t dest_ip, uint16_t port);
        static void udp_receive_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
    private:
        bool connected = false;
        bool udp_initialized = false;

};