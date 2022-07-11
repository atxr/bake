#pragma once
#include "server/ComputationServer.hpp"

class Client
{
public:
    Client(int id, FuzzyVault vault);

private:
    int id;
    FuzzyVault vault;
};