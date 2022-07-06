#include <openssl/ec.h> 
#include <openssl/bn.h> 
#include <openssl/obj_mac.h> 
#include "ec.hpp"

class Core
{
public:
static Point hashToCurve(Group G, BigInt hash);
};
