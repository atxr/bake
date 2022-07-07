#include <iostream>
#include <openssl/ec.h>
#include "core/Core.hpp"

using namespace std;

int main() {
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

    Point b = Core::blind(p, r);
    Point u = Core::unblind(b, r);
    if (p != b) {
        cout << "Blinding OK" << endl;
    }

    if (p == u) {
        cout << "Unblinding OK" << endl;
    }

    return 0;
}