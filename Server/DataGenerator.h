#pragma once
#include "../Common/Packet.h"

class DataGenerator {
public:
    GpsPacket generateGps();
    ScopePacket generateScope();
};
