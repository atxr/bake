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

    Point b = Core::blind(p, r);
    Point u = Core::unblind(b, r);
    if (p != b && p == u) {
        cout << "Blinding OK" << endl;
    }
    return 0;
}