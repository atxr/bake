#include <iostream>
#include <openssl/ec.h>
#include "core/Core.hpp"

using namespace std;

int main()
{
    // Test hashToCurve
    Group ECGroup;
    BigInt hash, r;
    ECGroup.get_rand_bn(hash);
    ECGroup.get_rand_bn(r);

    Point P;
    P.fromHash(&ECGroup, hash);

    if (P.is_on_curve())
    {
        std::cout << "HashToCurve generated a point P on the curve" << std::endl;
    }
    else
    {
        std::cout << "HashToCurve didn't generate a point on the curve" << std::endl;
    }

    // Test curveToHash
    BigInt hash2 = P.toHash();
    std::cout << "Hashing point P ... " << endl;
    BN_print_fp(stdout, hash2.n);
    std::cout << std::endl;
    return 0;
}