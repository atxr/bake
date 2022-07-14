#pragma once

#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/obj_mac.h>
#include "ec.hpp"

Point blind(const Point p, const BigInt r);
Point unblind(const Point b, const BigInt r);
BigInt hashKeychain(Point k1, Point k2, Point k3, Point k4, Point k5, Point k6, Point k7);

class FuzzyVault{};
class Query{};