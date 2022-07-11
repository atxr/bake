#include "Core.hpp"
#include <iostream>
#include <openssl/sha.h>

void Core::hashToCurve(Point *ret, Group G, BigInt hash)
{
    *ret = Point();
    ret->fromHash(&G, hash);

    if (ret->is_on_curve())
    {
        std::cout << "HashToCurve generated a point p on the curve" << std::endl;
    }
    else
    {
        std::cout << "HashToCurve didn't generate a point on the curve" << std::endl;
    }
}

BigInt Core::curveToHash(Point p) {
    BigInt x, y;
    EC_POINT_get_affine_coordinates(p.group->ec_group, p.point, x.n, y.n, p.group->bn_ctx);
    unsigned char xbin[BN_num_bytes(x.n)];
    unsigned char ybin[BN_num_bytes(y.n)];
    BN_bn2bin(x.n, xbin);
    BN_bn2bin(y.n, ybin);
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA224_Update(&sha256, xbin, sizeof(xbin));
    SHA224_Update(&sha256, ybin, sizeof(ybin));
    SHA256_Final(hash, &sha256);

    BigInt ret;
    BN_bin2bn(hash, sizeof(hash), ret.n);
    return ret;
}

Point Core::blind(const Point p, const BigInt r)
{
    Point b(p);
    b = b.mul(r);
    return b;
}

Point Core::unblind(const Point b, const BigInt r)
{
    Point p(b);
    BigInt inv_r(r);
    inv_r = r.inv_mod(b.group->order, b.group->bn_ctx);
    p = p.mul(inv_r);
    return p;
}