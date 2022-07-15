#include "ComputationServer.hpp"

ComputationServer::ComputationServer(AuthenticationServer as) : as(as)
{
    ECGroup = as.getGroup();
    ECGroup->get_rand_point(G);
}

Group *ComputationServer::getGroup() { return as.getGroup(); }
Point ComputationServer::getPublicGenerator() { return G; }
unsigned int ComputationServer::getClientId(FuzzyVault vault) { return 0; } // TODO tmp
FuzzyVault ComputationServer::getVault(unsigned int id) { return clients[id]->first; } // TODO tmp

ServerKeychain ComputationServer::getServerKeychain(unsigned int id, Point Cpk_e)
{
    ServerKeychain keychain;
    keychain.st = false;

    // Recover client stored public key
    Point Cpk_r = clients[id]->second;

    // Generate two key pairs
    BigInt ssk, ssk_e;
    ECGroup->get_rand_bn(ssk);
    ECGroup->get_rand_bn(ssk_e);
    Point Spk = G.mul(ssk);
    Point Spk_e = G.mul(ssk_e);

    // Compute final key ks
    BigInt ks = KDF(Cpk_e.mul(ssk_e), Cpk_e.mul(ssk),
                             Cpk_r.mul(ssk_e), Cpk_e,
                             Spk_e, Cpk_r, Spk);

    keychain.Spk = Spk;
    keychain.Spk_e = Spk_e;
    keychain.ks = ks;
    keychain.st = true;
    return keychain;
}

Point ComputationServer::sign(Point B)
{
    return as.sign(B);
}

bool ComputationServer::store(FuzzyVault vault, unsigned int id, Point Cpk_r)
{
    clients[id] = new StoredClient(vault, Cpk_r);
    return true;
}
