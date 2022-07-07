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

    return point;
}