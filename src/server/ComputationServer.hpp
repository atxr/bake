#pragma once
#include "AuthenticationServer.hpp"
#include <unordered_map>
#include <utility>

using StoredClient = std::pair<FuzzyVault, BigInt>;

class ComputationServer
{
public:
    ComputationServer(AuthenticationServer as);

private:
    AuthenticationServer as;
    std::unordered_map<int, StoredClient *> clients;
};