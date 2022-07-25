#include "Thimble.hpp"

MinutiaeView getMinutiaeView(string path)
{
    FJFXFingerprint fingerprint;
    if (!fingerprint.fromImageFile(path))
    {
        cerr << "Could not read " << path << endl;
        exit(1);
    }
    DirectedPoint refPoint = fingerprint.getDirectedReferencePoint();

    // Access the non-empty minutiae template
    MinutiaeView minutiaeView = fingerprint.getMinutiaeView();
    minutiaeView = FingerTools::prealign(minutiaeView, refPoint);
    return minutiaeView;
}

BytesVault fuzzyVault2Bytes(ProtectedMinutiaeTemplate vault)
{
    BytesVault data;
    int size, wsize;

    // Initialize byte array ...
    size = vault.getSizeInBytes();
    data = (uint8_t *)malloc(size * sizeof(uint8_t));
    if (data == NULL)
    {
        cerr << "byteFuzzyVault: "
             << "out of memory." << endl;
        exit(EXIT_FAILURE);
    }

    // ... in which this protected minutiae template is packed.
    vault.toBytes(data);
    return data;
}

ProtectedMinutiaeTemplate bytes2FuzzyVault(BytesVault data)
{
    ProtectedMinutiaeTemplate vault;
    vault.fromBytes(data, sizeof(data));
    return vault;
}