#pragma once
#include "AuthenticationServer.hpp"
#include <unordered_map>
#include <utility>

using StoredClient = std::pair<FuzzyVault, Point>;

class ComputationServer
{
public:
    ComputationServer(AuthenticationServer as);
    Group* getGroup();
    Point getPublicGenerator();
    unsigned int getClientId();
    Point sign(FuzzyVault vault, unsigned int id, Point r);
    bool store(FuzzyVault vault, unsigned int id, Point cpk_r);

private:
    AuthenticationServer as;
    Point h;
    std::unordered_map<int, StoredClient *> clients;
};