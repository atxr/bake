#pragma once
#include "AuthenticationServer.hpp"
#include <unordered_map>

using StoredClient = std::pair<BytesVault, Point>;

struct ServerKeychain {
    Point Spk, Spk_e, S;
    BigInt h_ks; 
    bool st;
}; 

class ComputationServer
{
public:
    ComputationServer(AuthenticationServer as);
    Group* getGroup();
    Point getPublicGenerator();
    BytesVault getVault(unsigned int id);
    Point signToEnroll(BytesVault vault, Point B, unsigned int id);
    ServerKeychain signToVerify(unsigned int id, Point B, Point Cpk_e);
    bool store(BytesVault vault, unsigned int id, Point Cpk_r);

private:
    ServerKeychain getServerKeychain(unsigned int id, Point Cpk_e);

    AuthenticationServer as;
    Group *ECGroup;
    Point G;
    std::unordered_map<int, StoredClient *> clients;
    BigInt ssk;
    Point Spk;
};