#include "ComputationServer.hpp"

ComputationServer::ComputationServer(AuthenticationServer as) : as(as)
{
    ECGroup = as.getGroup();
    ECGroup->get_rand_point(G);

    // Generate server key pair
    KeyPair sk = keygen(ECGroup);
    ssk = sk.first;
    Spk = sk.second;
}

Group *ComputationServer::getGroup() { return as.getGroup(); }
Point ComputationServer::getPublicGenerator() { return G; }
FuzzyVault ComputationServer::getVault(unsigned int id) { return clients[id]->first; } // TODO tmp

ServerKeychain ComputationServer::getServerKeychain(unsigned int id, Point Cpk_e)
{
    ServerKeychain keychain;
    keychain.st = false;

    // Recover client stored public key
    Point Cpk_r = clients[id]->second;

    // Generate an exchange key pair
    KeyPair sk_e = keygen(ECGroup);
    BigInt ssk_e = sk_e.first;
    Point Spk_e = sk_e.second;

    // Compute final key ks
    BigInt ks = KDF(Cpk_e.mul(ssk_e), Cpk_e.mul(ssk),
                             Cpk_r.mul(ssk_e), Cpk_e,
                             Spk_e, Cpk_r, Spk);

    keychain.Spk = Spk;
    keychain.Spk_e = Spk_e;
    keychain.h_ks = ks.toHash();
    return keychain;
}

Point ComputationServer::signToEnroll(FuzzyVault vault, Point B, unsigned int id)
{
    // TODO store temp vault and id
    return as.sign(B);
}

bool ComputationServer::store(FuzzyVault vault, unsigned int id, Point Cpk_r)
{
    clients[id] = new StoredClient(vault, Cpk_r);
    return true;
}

ServerKeychain ComputationServer::signToVerify(unsigned int id, Point B, Point Cpk_e)
{
    ServerKeychain keychain = getServerKeychain(id, Cpk_e);
    
    keychain.S = as.sign(B);
    keychain.st = true;
    return keychain;
}
