#include <iostream>
#include <openssl/ec.h>
#include "core/Core.hpp"
#include "fuzzyVault/Thimble.hpp"

using namespace std;

int main(int argc, char **argv)
{
    // Values for the mcyt database
    int width(256);
    int height(400);
    int dpi(500);

    if (argc != 3)
    {
        cout << "Error\nUsage: fuzzyvault <path to reference image> <path to query image>" << endl;
        exit(1);
    }

    ProtectedMinutiaeTemplate vault(width, height, dpi);
    MinutiaeView ref = getMinutiaeView(argv[1]);
    if (vault.enroll(ref))
    {
        cout << "Vault locked" << endl;
    }

    uint8_t* vaultBytes = fuzzyVault2bytes(vault);

    // ... ///

    ProtectedMinutiaeTemplate recVault;
    recVault.fromBytes(vaultBytes, sizeof(vaultBytes));
    MinutiaeView query = getMinutiaeView(argv[2]);
    SmallBinaryFieldPolynomial f(vault.getField());
    if (vault.open(f, query))
    {
        cout << "Vault unlocked" << endl;
    }

    return 0;
}