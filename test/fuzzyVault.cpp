#include <iostream>
#include <openssl/ec.h>
#include "core/Core.hpp"

using namespace std;

int main(int argc, char **argv)
{


    if (argc != 3)
    {
        cout << "Error\nUsage: fuzzyvault <path to reference image> <path to query image>" << endl;
        exit(1);
    }

    ProtectedMinutiaeTemplate vault(mcytWidth, mcytHeight, mcytDpi);
    MinutiaeView ref = getMinutiaeView(argv[1]);
    if (vault.enroll(ref))
    {
        cout << "Vault locked" << endl;
    }
    else
    {
        cout << "Failed to lock the vault with the reference " << argv[1] << endl;
        exit(1);
    }

    MinutiaeView query = getMinutiaeView(argv[2]);
    SmallBinaryFieldPolynomial f(vault.getField());
    if (vault.open(f, query))
    {
        cout << "Vault unlocked" << endl;
        cout << "f(0) = " << f.eval(0) << endl;
    }
    else
    {
        cout << "Failed to unlock the vault with the query " << argv[2] << endl;
    }

    return 0;
}