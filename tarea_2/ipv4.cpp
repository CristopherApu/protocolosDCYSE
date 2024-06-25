#include "ipv4.h"

std::vector<unsigned char> encapsulate_ipv4(const IPv4Packet& paquete) {
    std::vector<unsigned char> output;
    // Empaquetar los campos del encabezado IPv4 en el vector output
    output.push_back(paquete.ttl);
    output.push_back(paquete.id & 0xFF);
    output.push_back((paquete.id >> 8) & 0xFF);
    output.push_back(paquete.src_ip & 0xFF);
    output.push_back((paquete.src_ip >> 8) & 0xFF);
    output.push_back((paquete.src_ip >> 16) & 0xFF);
    output.push_back((paquete.src_ip >> 24) & 0xFF);
    output.push_back(paquete.dest_ip & 0xFF);
    output.push_back((paquete.dest_ip >> 8) & 0xFF);
    output.push_back((paquete.dest_ip >> 16) & 0xFF);
    output.push_back((paquete.dest_ip >> 24) & 0xFF);
    output.insert(output.end(), paquete.data.begin(), paquete.data.end());
    return output;
}

IPv4Packet decapsulate_ipv4(const std::vector<unsigned char>& input) {
    IPv4Packet paquete;
    // Desempaquetar los campos del encabezado IPv4 desde el vector input
    paquete.ttl = input[0];
    paquete.id = input[1] | (input[2] << 8);
    paquete.src_ip = input[3] | (input[4] << 8) | (input[5] << 16) | (input[6] << 24);
    paquete.dest_ip = input[7] | (input[8] << 8) | (input[9] << 16) | (input[10] << 24);
    paquete.data.assign(input.begin() + 11, input.end());
    return paquete;
}
