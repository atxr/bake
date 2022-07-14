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

Point blind(const Point p, const BigInt r)
{
    Point b(p);
    b = b.mul(r);
    return b;
}

Point unblind(const Point b, const BigInt r)
{
    Point p(b);
    BigInt inv_r(r);
    inv_r = r.inv_mod(b.group->order, b.group->bn_ctx);
    p = p.mul(inv_r);
    return p;
}

BigInt hashKeychain(Point k1, Point k2, Point k3, Point k4, Point k5, Point k6, Point k7)
{
    Point p(k1);
    Point k[6] = {k2, k3, k4, k5, k6, k7};
    for (int i = 0; i < 6; i++)
    {
        p = p.add(k[i]);
    }
    return p.toHash();
}

#endif