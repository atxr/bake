#pragma once
#include "server/ComputationServer.hpp"

class Client
{
public:
    Client(ComputationServer cs);
    bool init();
    bool enroll(MinutiaeView ref);
    bool verify(MinutiaeView query);


private:
    ComputationServer cs;
    int id;
    static unsigned int count;
    Group *ECGroup;
    Point G;
    
    // temporary stored f0
    BigInt tempf0;
};
