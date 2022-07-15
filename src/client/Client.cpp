#include "Client.hpp"
#include <iostream>

Client::Client(ComputationServer cs) : cs(cs) {}

bool Client::init()
{
    ECGroup = cs.getGroup();
    G = cs.getPublicGenerator();

    // Generate a random x at the moment
    ECGroup->get_rand_bn(tempf0);
    return true;
}

bool Client::enroll(FuzzyVault vault)
{
    // ask to the cs an id with a given vault
    // verify that the vault isn't already registered
    // and get a new id
    // cs stores the pair id,vault temporarly
    // and waits for the Cpk_r to store it definitively
    id = cs.getClientId(vault);

    // BigInt x = vault.getf0();
    // use the temporary stored x
    BigInt x = tempf0;
    std::cout << "x enroll: 0x";
    BN_print_fp(stdout, x.n);
    std::cout << std::endl;

    BigInt csk_r = generateSecretKey(x);
    // TODO error catch
    Point Cpk_r = G.mul(csk_r);

    std::cout << "Storing" << std::endl;
    bool st = cs.store(vault, id, Cpk_r);
    if (!st)
    {
        std::cout << "Failed: Storing" << std::endl;
    }
    return st;
}

BigInt Client::generateSecretKey(BigInt x)
{
    Point X;
    X.fromHash(ECGroup, x);
    BigInt r;
    ECGroup->get_rand_bn(r);
    Point B = blind(X, r);

    std::cout << "Signing" << std::endl;
    Point S = cs.sign(B);
    if (S.is_empty())
    {
        std::cout << "Failed: S is empty" << std::endl;
        return BigInt();
    }

    Point U = unblind(S, r);
    BigInt csk = U.toHash();
    return csk;
}

bool Client::verify(Query Q)
{
    FuzzyVault vault = cs.getVault(id);
    // BigInt x = vault.getf0(Q);
    // use the temporary stored x
    BigInt x = tempf0;
    // or use a random x (must fail)
    // ECGroup->get_rand_bn(x);
    std::cout << "x enroll: 0x";
    BN_print_fp(stdout, x.n);
    std::cout << std::endl;

    // Generate the probe key pair
    // TODO error catch
    BigInt csk_p = generateSecretKey(x);
    Point Cpk_p = G.mul(csk_p);

    // Generate new exchange key pair
    BigInt csk_e;
    ECGroup->get_rand_bn(csk_e);
    Point Cpk_e = G.mul(csk_e);

    // send the exchange public key to the computation server and get the server keychain
    std::cout << "Exchanging keys" << std::endl;
    ServerKeychain sKeychain = cs.getServerKeychain(id, Cpk_e);
    if (!sKeychain.st)
    {
        std::cout << "Failed during the exchange" << std::endl;
    }

    // compute the final client key
    BigInt kc = KDF(sKeychain.Spk_e.mul(csk_e),
                             sKeychain.Spk.mul(csk_e),
                             sKeychain.Spk_e.mul(csk_p),
                             Cpk_e, sKeychain.Spk_e,
                             Cpk_p, sKeychain.Spk);

    // compare the final keys
    std::cout << "H(kc) : 0x";
    BN_print_fp(stdout, kc.n);
    std::cout << std::endl;
    std::cout << "H(ks) : 0x";
    BN_print_fp(stdout, sKeychain.ks.n);
    std::cout << std::endl;
    return kc == sKeychain.ks;
}
