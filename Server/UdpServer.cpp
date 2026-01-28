#include "UdpServer.h"
#include "../Common/Logger.h"
#include <iostream>

UdpServer::UdpServer() : sock(INVALID_SOCKET) {}

UdpServer::~UdpServer() {
    if (sock != INVALID_SOCKET) closesocket(sock);
    WSACleanup();
}

bool UdpServer::init(uint16_t port) {
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

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        LOG_ERROR("Bind failed");
        return false;
    }

    // Setup broadcast
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (const char*)&opt, sizeof(opt));

    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_port = htons(port);
    broadcastAddr.sin_addr.s_addr = INADDR_BROADCAST;

    LOG_INFO("UDP Server initialized");
    return true;
}

void UdpServer::sendTo(const sockaddr_in& client, const uint8_t* data, size_t size) {
    sendto(sock, (const char*)data, size, 0, (sockaddr*)&client, sizeof(client));
}

void UdpServer::sendBroadcast(const uint8_t* data, size_t size) {
    sendto(sock, (const char*)data, size, 0, (sockaddr*)&broadcastAddr, sizeof(broadcastAddr));
}

void UdpServer::sendMulticast(const std::string& multicastIP, const uint8_t* data, size_t size) {
    sockaddr_in mcastAddr{};
    mcastAddr.sin_family = AF_INET;
    mcastAddr.sin_port = broadcastAddr.sin_port;
    inet_pton(AF_INET, multicastIP.c_str(), &mcastAddr.sin_addr);

    sendto(sock, (const char*)data, size, 0, (sockaddr*)&mcastAddr, sizeof(mcastAddr));
}
