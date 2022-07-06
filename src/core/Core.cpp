#include "Core.hpp"

Point Core::hashToCurve(Group G, BigInt hash) {
    Point point;
    point.fromHash(&G, hash);
    return point;
}