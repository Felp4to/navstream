#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdint>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

class UdpServer {
public:
    UdpServer();
    ~UdpServer();

    bool init(uint16_t port);
    void sendTo(const sockaddr_in& client, const uint8_t* data, size_t size);
    void sendBroadcast(const uint8_t* data, size_t size);
    void sendMulticast(const std::string& multicastIP, const uint8_t* data, size_t size);

private:
    SOCKET sock;
    sockaddr_in broadcastAddr;
};