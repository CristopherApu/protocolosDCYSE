#ifndef IPV4_H
#define IPV4_H

#include <cstdint>
#include <vector>

#define MAX_DATA_SIZE 1500

struct IPv4Packet {
    uint8_t fragment_flag;
    uint16_t fragment_offset;
    uint16_t data_length;
    uint8_t ttl;
    uint16_t identification;
    uint16_t checksum;
    uint32_t ip_source;
    uint32_t ip_destination;
    std::vector<unsigned char> data;

    IPv4Packet() : data(MAX_DATA_SIZE) {}
};

#endif // IPV4_H