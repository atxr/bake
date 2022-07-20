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
    // TODO compute smarter id like the hash of the fuzzy vault? or a random one?
    id = 0;

    // BigInt x = vault.getf0();
    // use the temporary stored x
    BigInt x = tempf0;
    std::cout << "x enroll: 0x";
    BN_print_fp(stdout, x.n);
    std::cout << std::endl;

    // Generate the blinded point
    BlindedPair bp = blind(x, ECGroup);
    Point B = bp.first;
    BigInt r = bp.second;

    // First communication with the computation server
    std::cout << "Signing" << std::endl;
    Point S = cs.signToEnroll(vault, B, id);
    if (S.is_empty())
    {
        std::cout << "Failed: S is empty" << std::endl;
        return false;
    }

    // Compute key pair from the signed point
    Point U = unblind(S, r);
    BigInt csk_r = U.toHash();
    Point Cpk_r = G.mul(csk_r);

    // Second communication with the computation server
    std::cout << "Storing" << std::endl;
    bool st = cs.store(vault, id, Cpk_r);
    if (!st)
    {
        std::cout << "Failed: Storing" << std::endl;
    }
    return st;
}

bool Client::verify(Query Q)
{
    // First communication with the server
    std::cout << "Get vault stored on the computation server" << std::endl;
    // TODO catch error
    FuzzyVault vault = cs.getVault(id);

    // BigInt x = vault.getf0(Q);
    // use the temporary stored x
    BigInt x = tempf0;
    // or use a random x (must fail)
    // ECGroup->get_rand_bn(x);
    std::cout << "x enroll: 0x";
    BN_print_fp(stdout, x.n);
    std::cout << std::endl;

    // Generate the blinded point
    BlindedPair bp = blind(x, ECGroup);
    Point B = bp.first;
    BigInt r = bp.second;

    // Generate a new exchange key pair
    KeyPair ck_e = keygen(G, ECGroup);
    BigInt csk_e = ck_e.first;
    Point Cpk_e = ck_e.second;

    // Second communication with the server
    std::cout << "Get signed server keychain" << std::endl;
    ServerKeychain sKeychain = cs.signToVerify(id, B, Cpk_e);
    if (sKeychain.st == false)
    {
        std::cout << "Failed: server keychain signing failed" << std::endl;
        return false;
    }

    // unblind the signed point
    Point U = unblind(sKeychain.S, r);
    BigInt csk_p = U.toHash();
    Point Cpk_p = G.mul(csk_p);

    // compute kc and H(kc)
    BigInt kc = KDF(sKeychain.Spk_e.mul(csk_e),
                             sKeychain.Spk.mul(csk_e),
                             sKeychain.Spk_e.mul(csk_p),
                             Cpk_e, sKeychain.Spk_e,
                             Cpk_p, sKeychain.Spk);
    BigInt h_kc = kc.toHash();

    // compare the final keys
    std::cout << "H(kc) : 0x";
    BN_print_fp(stdout, h_kc.n);
    std::cout << std::endl;
    std::cout << "H(ks) : 0x";
    BN_print_fp(stdout, sKeychain.h_ks.n);
    std::cout << std::endl;
    return h_kc == sKeychain.h_ks;
}
