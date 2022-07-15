#ifndef CORE_CPP
#define CORE_CPP

#include <iostream>
#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/obj_mac.h>
#include <openssl/sha.h>
#include "ec.hpp"

class FuzzyVault
{
};

Point blind(const Point P, const BigInt r)
{
    Point B(P);
    B = B.mul(r);
    return B;
}

Point unblind(const Point B, const BigInt r)
{
    Point P(B);
    BigInt inv_r(r);
    inv_r = r.inv_mod(B.group->order, B.group->bn_ctx);
    P = P.mul(inv_r);
    return P;
}

BigInt KDF(Point K1, Point K2, Point K3, Point K4, Point K5, Point K6, Point K7)
{
    // TODO KDF function with concat of all coordinates
    Point P(K1);
    Point k[6] = {K2, K3, K4, K5, K6, K7};
    for (int i = 0; i < 6; i++)
    {
        P = P.add(k[i]);
    }
    return P.toHash();
}

#endif