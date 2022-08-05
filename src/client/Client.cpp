#include "Client.hpp"
#include <iostream>

Client::Client(ComputationServer cs) : cs(cs) {}
unsigned int Client::count = 0;

bool Client::init()
{
    ECGroup = cs.getGroup();
    G = cs.getPublicGenerator();

    // Generate a random x at the moment
    ECGroup->get_rand_bn(tempf0);
    return true;
}

bool Client::enroll(MinutiaeView ref, bool verbose)
{
    id = ++count;

    // Real version
    // Lock the vault
    FuzzyVaultBake vault(mcytWidth, mcytHeight, mcytDpi);
    if (!vault.enroll(ref))
    {
        cout << "Failed to lock the vault with the reference " << ref << endl;
        exit(1);
    }
    BytesVault bVault = vault.toBytesVault();

    // Open the vault and get f0
    BigInt x;
    x.fromInt(vault.getf0(ref));

    // Debug version
    // use the temporary stored x
    // BigInt x = tempf0;

    if (verbose)
    {
        std::cout << "x enroll: 0x";
        BN_print_fp(stdout, x.n);
        std::cout << std::endl;
    }

    // Generate the blinded point
    BlindedPair bp = blind(x, ECGroup);
    Point B = bp.first;
    BigInt r = bp.second;

    // First communication with the computation server
    if (verbose)
    {
        std::cout << "Signing" << std::endl;
    }
    Point S = cs.signToEnroll(bVault, B, id);
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
    if (verbose)
    {
        std::cout << "Storing" << std::endl;
    }
    bool st = cs.store(bVault, id, Cpk_r);
    if (!st)
    {
        std::cout << "Failed: Storing" << std::endl;
    }
    return st;
}

bool Client::verify(MinutiaeView query, bool verbose)
{
    // First communication with the server
    if (verbose)
    {
        std::cout << "Get vault stored on the computation server" << std::endl;
    }
    BytesVault bv = cs.getVault(id);
    FuzzyVaultBake vault(bv);

    // Real version
    uint32_t f0 = vault.getf0(query);
    if (f0 == -1)
    {
        if (verbose)
        {
            cout << "Cannot recover f(0) with this vault" << endl;
        }
        return false;
    }
    BigInt x;
    x.fromInt(f0);

    // Debug version
    // use the temporary stored x
    // x = tempf0
    // or use a random x (must fail)
    // ECGroup->get_rand_bn(x);

    if (verbose)
    {
        std::cout << "x verify: 0x";
        BN_print_fp(stdout, x.n);
        std::cout << std::endl;
    }

    // Generate the blinded point
    Point B;
    BigInt r;
    std::tie(B, r) = blind(x, ECGroup);

    // Generate a new exchange key pair
    BigInt csk_e;
    Point Cpk_e;
    std::tie(csk_e, Cpk_e) = keygen(G, ECGroup);

    // Second communication with the server
    if (verbose)
    {
        std::cout << "Get signed server keychain" << std::endl;
    }
    ServerKeychain sKeychain = cs.signToVerify(id, B, Cpk_e);
    if (sKeychain.st == false)
    {
        std::cout << "Failed: server keychain signing failed" << std::endl;
        return false;
    }

    // unblind the signed point
    Point U = unblind(sKeychain.S, r);
    BigInt csk_p = U.toHash();
    Point Cpk_p = getPublicKey(csk_p, G);

    // compute kc and H(kc)
    BigInt kc = KDF(sKeychain.Spk_e.mul(csk_e),
                    sKeychain.Spk.mul(csk_e),
                    sKeychain.Spk_e.mul(csk_p),
                    Cpk_e, sKeychain.Spk_e,
                    Cpk_p, sKeychain.Spk);
    BigInt h_kc = kc.toHash();

    // compare the final keys
    if (verbose)
    {
        std::cout << "H(kc) : 0x";
        BN_print_fp(stdout, h_kc.n);
        std::cout << std::endl;
        std::cout << "H(ks) : 0x";
        BN_print_fp(stdout, sKeychain.h_ks.n);
        std::cout << std::endl;
    }
    return h_kc == sKeychain.h_ks;
}
