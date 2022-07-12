#include "ComputationServer.hpp"

Group* ComputationServer::getGroup() { return as.getGroup(); }
Point ComputationServer::getPublicGenerator() { return h; }
unsigned int ComputationServer::getClientId() { return 0; } // TODO tmp

Point ComputationServer::sign(FuzzyVault vault, unsigned int id, Point r)
{
    return as.sign(r);
}
bool ComputationServer::store(FuzzyVault vault, unsigned int id, BigInt cpk_r)
{
    clients[id] = new StoredClient(vault, cpk_r);
    return true;
}
