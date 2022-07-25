#pragma once
#include "FJFXFingerprint.hpp"

using BytesVault = uint8_t*;

MinutiaeView getMinutiaeView(string image);
BytesVault fuzzyVault2Bytes(ProtectedMinutiaeTemplate vault);
ProtectedMinutiaeTemplate bytes2FuzzyVault(BytesVault data);
uint32_t getf0(BytesVault bVault, MinutiaeView view);