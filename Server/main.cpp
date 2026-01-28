#include "UdpServer.h"
#include "DataGenerator.h"
#include "../Common/Protocol.h"
#include "../Common/Logger.h"
#include <thread>
#include <chrono>


int main() {
    UdpServer server;
    if (!server.init(5000)) return -1;

    DataGenerator generator;

    LOG_INFO("Server started");

    while (true) {
        auto gps = generator.generateGps();
        auto gpsData = Protocol::serializeGps(gps);
        server.sendBroadcast(gpsData.data(), gpsData.size());
        LOG_DEBUG("GPS packet sent");

        auto scope = generator.generateScope();
        auto scopeData = Protocol::serializeScope(scope);
        server.sendBroadcast(scopeData.data(), scopeData.size());
        LOG_DEBUG("Scope packet sent");

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
