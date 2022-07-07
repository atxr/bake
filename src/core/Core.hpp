#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/obj_mac.h>
#include "ec.hpp"

class Core
{
public:
    static void hashToCurve(Point *ret, Group G, BigInt hash);
    static Point blind(const Point p, const BigInt r);
    static Point unblind(const Point b, const BigInt r);
};