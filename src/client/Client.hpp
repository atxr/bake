#pragma once
#include "server/ComputationServer.hpp"

class Client
{
public:
    Client(int id, FuzzyVault vault);
    bool enroll(ComputationServer cs);

private:
    int id;
    FuzzyVault vault;
};