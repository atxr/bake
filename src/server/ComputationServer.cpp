#include "ComputationServer.hpp"

ComputationServer::ComputationServer(AuthenticationServer as) : as(as)
{
    as.getGroup()->get_rand_point(h);
}

Group* ComputationServer::getGroup() { return as.getGroup(); }
Point ComputationServer::getPublicGenerator() { return h; }
unsigned int ComputationServer::getClientId() { return 0; } // TODO tmp

Point ComputationServer::sign(FuzzyVault vault, unsigned int id, Point r)
{
    return as.sign(r);
}

bool ComputationServer::store(FuzzyVault vault, unsigned int id, Point cpk_r)
{
    clients[id] = new StoredClient(vault, cpk_r);
    return true;
}
