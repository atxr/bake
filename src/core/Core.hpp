#pragma once

#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/obj_mac.h>
#include <utility>
#include "ec.hpp"

using KeyPair = std::pair<BigInt, Point>;

Point blind(const Point P, const BigInt r);
Point unblind(const Point B, const BigInt r);
BigInt KDF(Point K1, Point K2, Point K3, Point K4, Point K5, Point K6, Point K7);
KeyPair keygen(Group *ECGroup);

class FuzzyVault
{
};
class Query
{
};