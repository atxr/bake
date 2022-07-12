#pragma once
#include "server/ComputationServer.hpp"

class Client
{
public:
    Client(ComputationServer cs);
    bool init();
    bool enroll(FuzzyVault vault);

private:
    Point generatePublicKey(FuzzyVault vault);

    ComputationServer cs;
    int id;
    Group *G;
    Point h;
};