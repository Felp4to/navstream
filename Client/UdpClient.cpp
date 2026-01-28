#include "UdpClient.h"
#include "../Common/Protocol.h"
#include "../Common/Logger.h"
#include <iostream>

UdpClient::UdpClient() : sock(INVALID_SOCKET) {}

UdpClient::~UdpClient() {
    if (sock != INVALID_SOCKET) closesocket(sock);
    WSACleanup();
}

bool UdpClient::init(uint16_t port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        LOG_ERROR("WSAStartup failed");
        return false;
    }

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        LOG_ERROR("Socket creation failed");
        return false;
    }

    sockaddr_in clientAddr{};
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = INADDR_ANY;
    clientAddr.sin_port = htons(port);

    if (bind(sock, (sockaddr*)&clientAddr, sizeof(clientAddr)) == SOCKET_ERROR) {
        LOG_ERROR("Bind failed");
        return false;
    }

    LOG_INFO("UDP Client initialized");
    return true;
}

void UdpClient::receiveLoop() {
    uint8_t buffer[1024];
    sockaddr_in from{};
    int fromLen = sizeof(from);

    int bytes = recvfrom(sock, (char*)buffer, sizeof(buffer), 0,
        (sockaddr*)&from, &fromLen);
    if (bytes <= 0) return;

    PacketHeader* header = (PacketHeader*)buffer;

    if (header->type == PacketType::GPS) {
        auto gps = Protocol::deserializeGps(buffer, bytes);
        LOG_INFO("Received GPS: lat=" + std::to_string(gps.lat) +
            " lon=" + std::to_string(gps.lon) +
            " alt=" + std::to_string(gps.alt));
    }
    else if (header->type == PacketType::SCOPE) {
        auto scope = Protocol::deserializeScope(buffer, bytes);
        LOG_INFO("Received Scope packet first sample=" + std::to_string(scope.samples[0]));
    }
}
