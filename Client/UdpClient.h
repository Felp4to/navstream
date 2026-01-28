#pragma once
#include <winsock2.h>
#include <cstdint>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

class UdpClient {
public:
    UdpClient();
    ~UdpClient();

    bool init(uint16_t port);
    void receiveLoop();

private:
    SOCKET sock;
};
