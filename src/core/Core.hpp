#pragma once

#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/obj_mac.h>
#include "ec.hpp"

Point blind(const Point P, const BigInt r);
Point unblind(const Point B, const BigInt r);
BigInt KDF(Point K1, Point K2, Point K3, Point K4, Point K5, Point K6, Point K7);

class FuzzyVault{};
class Query{};