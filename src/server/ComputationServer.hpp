#pragma once
#include "AuthenticationServer.hpp"
#include <unordered_map>
#include <utility>

using StoredClient = std::pair<FuzzyVault, Point>;

struct ServerKeychain {
    Point spk, spk_e;
    BigInt ks; 
    bool st;
}; 

class ComputationServer
{
public:
    ComputationServer(AuthenticationServer as);
    Group* getGroup();
    Point getPublicGenerator();
    unsigned int getClientId(FuzzyVault vault);
    FuzzyVault getVault(unsigned int id);
    ServerKeychain getServerKeychain(unsigned int id, Point cpk_e);
    Point sign(Point r);
    bool store(FuzzyVault vault, unsigned int id, Point cpk_r);

private:
    AuthenticationServer as;
    Group *G;
    Point h;
    std::unordered_map<int, StoredClient *> clients;
};