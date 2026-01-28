#include "UdpClient.h"
#include "../Common/Logger.h"
#include <thread>

int main() {
    UdpClient client;
    if (!client.init(5000)) return -1;

    LOG_INFO("Client started");

    while (true) {
        client.receiveLoop();
    }

    return 0;
}