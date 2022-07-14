#pragma once
#include "server/ComputationServer.hpp"

class Client
{
public:
    Client(ComputationServer cs);
    bool init();
    bool enroll(FuzzyVault vault);

private:
    BigInt generateSecretKey(BigInt f0);

    ComputationServer cs;
    int id;
    Group *G;
    Point h;
    
    // temporary stored f0
    BigInt tempf0;
};