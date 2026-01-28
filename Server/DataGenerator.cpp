#include "DataGenerator.h"
#include <cstdlib>
#include <ctime>

GpsPacket DataGenerator::generateGps() {
    GpsPacket gps{};
    gps.lat = (rand() % 18000 - 9000) / 100.0;   // -90..+90
    gps.lon = (rand() % 36000 - 18000) / 100.0; // -180..+180
    gps.alt = (rand() % 5000) / 10.0;           // 0..500 m
    return gps;
}

ScopePacket DataGenerator::generateScope() {
    ScopePacket scope{};
    for (int i = 0; i < MAX_SAMPLES; ++i)
        scope.samples[i] = (float)(rand() % 1000) / 10.0f;
    return scope;
}
