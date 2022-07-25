#pragma once
#include "FJFXFingerprint.hpp"

using BytesVault = uint8_t*;

MinutiaeView getMinutiaeView(string image);
BytesVault fuzzyVault2Bytes(ProtectedMinutiaeTemplate vault);
ProtectedMinutiaeTemplate bytes2FuzzyVault(BytesVault data);