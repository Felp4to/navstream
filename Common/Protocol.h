#pragma once
#include "Packet.h"
#include <vector>
#include <cstring>
#include <stdexcept>
#include <chrono>

namespace Protocol {

    inline uint64_t now_ms() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    }

    // Serializzazione GPS
    inline std::vector<uint8_t> serializeGps(const GpsPacket& gps) {
        std::vector<uint8_t> buffer(sizeof(PacketHeader) + sizeof(GpsPacket));
        PacketHeader header{};
        header.type = PacketType::GPS;
        header.payloadSize = sizeof(GpsPacket);
        header.timestamp = now_ms();

        std::memcpy(buffer.data(), &header, sizeof(header));
        std::memcpy(buffer.data() + sizeof(header), &gps, sizeof(gps));
        return buffer;
    }

    inline GpsPacket deserializeGps(const uint8_t* data, size_t size) {
        if (size < sizeof(PacketHeader) + sizeof(GpsPacket))
            throw std::runtime_error("Buffer troppo piccolo per GpsPacket");
        GpsPacket gps{};
        std::memcpy(&gps, data + sizeof(PacketHeader), sizeof(gps));
        return gps;
    }

    // Serializzazione Scope
    inline std::vector<uint8_t> serializeScope(const ScopePacket& scope) {
        std::vector<uint8_t> buffer(sizeof(PacketHeader) + sizeof(ScopePacket));
        PacketHeader header{};
        header.type = PacketType::SCOPE;
        header.payloadSize = sizeof(ScopePacket);
        header.timestamp = now_ms();

        std::memcpy(buffer.data(), &header, sizeof(header));
        std::memcpy(buffer.data() + sizeof(header), &scope, sizeof(scope));
        return buffer;
    }

    inline ScopePacket deserializeScope(const uint8_t* data, size_t size) {
        if (size < sizeof(PacketHeader) + sizeof(ScopePacket))
            throw std::runtime_error("Buffer troppo piccolo per ScopePacket");
        ScopePacket scope{};
        std::memcpy(&scope, data + sizeof(PacketHeader), sizeof(scope));
        return scope;
    }

} // namespace Protocol
