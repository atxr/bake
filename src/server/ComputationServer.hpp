#pragma once
#include "AuthenticationServer.hpp"
#include <unordered_map>
#include <utility>

using StoredClient = std::pair<FuzzyVault, BigInt>;

class ComputationServer
{
public:
    ComputationServer(AuthenticationServer as);
    Point sign(FuzzyVault vault, unsigned int id, Point r);
    bool store(FuzzyVault vault, unsigned int id, BigInt cpk_r);

private:
    AuthenticationServer as;
    std::unordered_map<int, StoredClient *> clients;
};