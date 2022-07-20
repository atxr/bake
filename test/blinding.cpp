#include <iostream>
#include <openssl/ec.h>
#include "core/Core.hpp"

using namespace std;

int main() {
    Group* ECGroup = new Group;
    BigInt hash;
    ECGroup->get_rand_bn(hash);

    Point P;
    P.fromHash(ECGroup, hash);

    BlindedPair bp = blind(hash, ECGroup);
    Point B = bp.first;
    BigInt r = bp.second;

    Point U = unblind(B, r);
    if (P != B && P == U) {
        cout << "Blinding OK" << endl;
    }
    return 0;
}