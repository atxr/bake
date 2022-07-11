#include "Client.hpp"
#include <iostream>

Client::Client(int id, FuzzyVault vault) : id(id), vault(vault) {}

bool Client::enroll(ComputationServer cs)
{
    Group G;
    // BigInt f0 = vault.getf0();

    // Generate a random f0 at the moment
    BigInt f0;
    G.get_rand_bn(f0);

    Point g;
    g.fromHash(&G, f0);
    BigInt b;
    G.get_rand_bn(b);
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
    BigInt h;
    G.get_rand_bn(h);
    BigInt cpk_r = h.exp_mod(csk_r, G); //= h^csk_r;
    std::cout << "Storing" << std::endl;
    bool st = cs.store(vault, id, cpk_r);
    if (!st) {
        std::cout << "Failed: Storing" << std::endl;
    }
    return st;
}