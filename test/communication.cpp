#include <iostream>
#include <openssl/ec.h>
#include "client/Client.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Group ECGroup;
    BigInt r;
    Point P;
    ECGroup.get_rand_bn(r);
    P.fromHash(&ECGroup, r);
    cout << "Group element size: " << P.size() << endl;

    FuzzyVaultBake vault(mcytWidth, mcytHeight, mcytDpi, 8);
    vault.enroll(getMinutiaeView(argv[1]));
    BytesVault bv = vault.toBytesVault();
    cout << "Vault size for k = 8: " << bv.size << endl;
    return 0;
}