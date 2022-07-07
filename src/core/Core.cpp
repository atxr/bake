#include "Core.hpp"
#include <iostream>

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