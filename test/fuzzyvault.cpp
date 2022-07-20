#include <iostream>
#include <openssl/ec.h>
#include "core/Core.hpp"
#include "thimbleExt/FJFXFingerprint.h"

using namespace std;

// TODO move this to aux function in src/thimbleExt
bool lockFuzzyVault(MinutiaeFuzzyVault &vault, string image)
{
    FJFXFingerprint fingerprint;
    if (!fingerprint.fromImageFile(image))
    {
        cerr << "Could not read " << image << endl;
        return false;
    }
    DirectedPoint refPoint = fingerprint.getDirectedReferencePoint();

    // Access the non-empty minutiae template
    MinutiaeView minutiaeView = fingerprint.getMinutiaeView();
    minutiaeView = FingerTools::prealign(minutiaeView, refPoint);

    // Lock the vault from this minutiae view
    return vault.enroll(minutiaeView);
}

int main(int argc, char **argv)
{
    Group *ECGroup = new Group;
    BigInt hash;
    ECGroup->get_rand_bn(hash);

    Point P;
    P.fromHash(ECGroup, hash);

    MinutiaeFuzzyVault vault(256, 400);
    bool st = lockFuzzyVault(vault, argv[1]);
    if (st)
    {
        cout << "Vault locked" << endl;
    }

    return 0;
}