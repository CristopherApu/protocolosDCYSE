#ifndef IPV4_H
#define IPV4_H

#include <vector>
#include <cstdint>

// Definición de la estructura del paquete IPv4 modificado
struct IPv4Packet {
    uint8_t ttl;
    uint16_t id;
    uint32_t src_ip;
    uint32_t dest_ip;
    std::vector<unsigned char> data;
};

// Funciones para encapsular y desencapsular el paquete IPv4 modificado
std::vector<unsigned char> encapsulate_ipv4(const IPv4Packet& packet);
IPv4Packet decapsulate_ipv4(const std::vector<unsigned char>& input);

#endif // IPV4_H