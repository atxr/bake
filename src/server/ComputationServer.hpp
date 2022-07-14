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
    unsigned int getClientId(FuzzyVault vault);
    Point sign(Point r);
    bool store(FuzzyVault vault, unsigned int id, Point cpk_r);

private:
    AuthenticationServer as;
    Group *G;
    Point h;
    std::unordered_map<int, StoredClient *> clients;
};