#include "ComputationServer.hpp"

ComputationServer::ComputationServer(AuthenticationServer as) : as(as)
{
    G = as.getGroup();
    G->get_rand_point(h);
}

Group *ComputationServer::getGroup() { return as.getGroup(); }
Point ComputationServer::getPublicGenerator() { return h; }
unsigned int ComputationServer::getClientId(FuzzyVault vault) { return 0; } // TODO tmp
FuzzyVault ComputationServer::getVault(unsigned int id) { return clients[id]->first; } // TODO tmp

ServerKeychain ComputationServer::getServerKeychain(unsigned int id, Point cpk_e)
{
    ServerKeychain keychain;
    keychain.st = false;

    // Recover client stored public key
    Point cpk_r = clients[id]->second;

    // Generate two key pairs
    BigInt ssk, ssk_e;
    G->get_rand_bn(ssk);
    G->get_rand_bn(ssk_e);
    Point spk = h.mul(ssk);
    Point spk_e = h.mul(ssk_e);

    // Compute final key ks
    BigInt ks = hashKeychain(cpk_e.mul(ssk_e), cpk_e.mul(ssk),
                             cpk_r.mul(ssk_e), cpk_e,
                             spk_e, cpk_r, spk);

    keychain.spk = spk;
    keychain.spk_e = spk_e;
    keychain.ks = ks;
    keychain.st = true;
    return keychain;
}

Point ComputationServer::sign(Point r)
{
    return as.sign(r);
}

bool ComputationServer::store(FuzzyVault vault, unsigned int id, Point cpk_r)
{
    clients[id] = new StoredClient(vault, cpk_r);
    return true;
}
