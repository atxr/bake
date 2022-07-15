#include <iostream>
#include <openssl/ec.h>
#include "core/Core.hpp"

using namespace std;

int main() {
    Group ECGroup;
    BigInt hash, r;
    ECGroup.get_rand_bn(hash);
    ECGroup.get_rand_bn(r);

    Point P;
    P.fromHash(&ECGroup, hash);

    Point B = blind(P, r);
    Point U = unblind(B, r);
    if (P != B && P == U) {
        cout << "Blinding OK" << endl;
    }
    return 0;
}