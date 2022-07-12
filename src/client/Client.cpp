#include "Client.hpp"
#include <iostream>

Client::Client(ComputationServer cs) : cs(cs) {}

bool Client::init() {
    id = cs.getClientId();
    G = cs.getGroup();
    h = cs.getPublicGenerator();
    return true;
}

bool Client::enroll(FuzzyVault vault)
{
    // BigInt f0 = vault.getf0();

    // Generate a random f0 at the moment
    BigInt f0;
    G->get_rand_bn(f0);

    Point g;
    g.fromHash(G, f0);
    BigInt b;
    G->get_rand_bn(b);
    Point r = blind(g, b);
    
    std::cout << "Signing" << std::endl;
    Point r1 = cs.sign(vault, id, r);
    if (r1.is_empty())
    {
        std::cout << "Failed: r1 is empty" << std::endl;
        return false;
    }

    Point r2 = unblind(r1, b);
    BigInt csk_r = r2.toHash();
    Point cpk_r = blind(h, csk_r); // cpk_r = h^csk_r
    std::cout << "Storing" << std::endl;
    bool st = cs.store(vault, id, cpk_r);
    if (!st) {
        std::cout << "Failed: Storing" << std::endl;
    }
    return st;
}