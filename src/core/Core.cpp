#include "Core.hpp"
#include <iostream>

Point Core::hashToCurve(Group G, BigInt hash)
{
    Point point;
    point.fromHash(&G, hash);
    
    if (point.is_on_curve())
    {
        std::cout << "HashToCurve generated a point p on the curve" << std::endl;
    }
    else
    {
        std::cout << "HashToCurve didn't generate a point on the curve" << std::endl;
    }

    return point;
}