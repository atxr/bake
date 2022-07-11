#include "ComputationServer.hpp"

ComputationServer::ComputationServer(AuthenticationServer as) : as(as) {}

Point ComputationServer::sign(FuzzyVault vault, unsigned int id, Point r)
{
    return as.sign(r);
}
bool ComputationServer::store(FuzzyVault vault, unsigned int id, BigInt cpk_r)
{
    clients[id] = new StoredClient(vault, cpk_r);
    return true;
}
