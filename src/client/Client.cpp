#include "Client.hpp"
#include <iostream>

Client::Client(ComputationServer cs) : cs(cs) {}

bool Client::init()
{
    G = cs.getGroup();
    h = cs.getPublicGenerator();

    // Generate a random f0 at the moment
    G->get_rand_bn(tempf0);
    return true;
}

bool Client::enroll(FuzzyVault vault)
{
    // ask to the cs an id with a given vault
    // verify that the vault isn't already registered 
    // and get a new id
    // cs stores the pair id,vault temporarly
    // and waits for the cpk_r to store it definitively 
    id = cs.getClientId(vault);

    // BigInt f0 = vault.getf0();
    // use the temporary stored f0
    BigInt f0 = tempf0;

    BigInt csk_r = generateSecretKey(f0);
    // TODO error catch
    Point cpk_r = h.mul(csk_r);

    std::cout << "Storing" << std::endl;
    bool st = cs.store(vault, id, cpk_r);
    if (!st)
    {
        std::cout << "Failed: Storing" << std::endl;
    }
    return st;
}

BigInt Client::generateSecretKey(BigInt f0)
{
    Point g;
    g.fromHash(G, f0);
    BigInt b;
    G->get_rand_bn(b);
    Point r = blind(g, b);

    std::cout << "Signing" << std::endl;
    Point r1 = cs.sign(r);
    if (r1.is_empty())
    {
        std::cout << "Failed: r1 is empty" << std::endl;
        return BigInt();
    }

    Point r2 = unblind(r1, b);
    BigInt csk = r2.toHash();
    return csk;
}

bool Client::verify(Query Q)
{
    FuzzyVault vault = cs.getVault(id);
    // BigInt f0 = vault.getf0(Q);
    // use the temporary stored f0 
    BigInt f0 = tempf0;

    // Generate the probe key pair
    // TODO error catch
    BigInt csk_p = generateSecretKey(f0);
    Point cpk_p = h.mul(csk_p);

    // Generate new exchange key pair
    BigInt csk_e;
    G->get_rand_bn(csk_e);
    Point cpk_e = h.mul(csk_e);

    // send the exchange public key to the computation server and get the server keychain
    std::cout << "Exchanging keys" << std::endl;
    ServerKeychain sKeychain = cs.getServerKeychain(id, cpk_e);
    if (!sKeychain.st)
    {
        std::cout << "Failed during the exchange" << std::endl;
    }
    

    // compute the final client key 
    // TODO compute hashKeychain
    BigInt kc = hashKeychain(sKeychain.spk_e.mul(csk_e),
                             sKeychain.spk.mul(csk_e),
                             sKeychain.spk_e.mul(csk_p),
                             cpk_e, sKeychain.spk_e, cpk_p, sKeychain.spk);

    // compare the final keys
    return kc == sKeychain.ks;
}
