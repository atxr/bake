#pragma once
#include "server/ComputationServer.hpp"

class Client
{
public:
    Client(ComputationServer cs);
    bool init();
    bool enroll(FuzzyVault vault);
    bool verify(Query query);

private:
    BigInt generateSecretKey(BigInt f0);

    ComputationServer cs;
    int id;
    Group *ECGroup;
    Point G;
    
    // temporary stored f0
    BigInt tempf0;
};