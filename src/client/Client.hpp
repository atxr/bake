#pragma once
#include "server/ComputationServer.hpp"

class Client
{
public:
    Client(ComputationServer cs);
    bool init();
    bool enroll(FuzzyVault vault);

private:
    ComputationServer cs;
    int id;
    Group *G;
};