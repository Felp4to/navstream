#pragma once
#include <cstdint>

enum class PacketType : uint8_t {
    GPS = 1,
    SCOPE = 2
};

#pragma pack(push, 1)
struct PacketHeader {
    PacketType type;
    uint32_t payloadSize;
    uint64_t timestamp; // ms dal epoch
};

struct GpsPacket {
    double lat;
    double lon;
    double alt;
};

#define MAX_SAMPLES 128
struct ScopePacket {
    float samples[MAX_SAMPLES];
};
#pragma pack(pop)
