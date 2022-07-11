#include <iostream>
#include <openssl/ec.h>
#include "core/Core.hpp"

using namespace std;

int main()
{
    // Test hashToCurve
    Group G;
    BigInt hash, r;
    G.get_rand_bn(hash);
    G.get_rand_bn(r);

    Point p;
    p.fromHash(&G, hash);

    if (p.is_on_curve())
    {
        std::cout << "HashToCurve generated a point p on the curve" << std::endl;
    }
    else
    {
        std::cout << "HashToCurve didn't generate a point on the curve" << std::endl;
    }

    // Test curveToHash
    BigInt hash2 = p.toHash();
    std::cout << "Hashing point p ... " << endl;
    BN_print_fp(stdout, hash2.n);
    std::cout << std::endl;
    return 0;
}