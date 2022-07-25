#pragma once
#include "FJFXFingerprint.hpp"

MinutiaeView getMinutiaeView(string image);
uint8_t *fuzzyVault2Bytes(ProtectedMinutiaeTemplate vault);
ProtectedMinutiaeTemplate bytes2FuzzyVault(uint8_t *data);