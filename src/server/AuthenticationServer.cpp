#include "AuthenticationServer.hpp"

AuthenticationServer::AuthenticationServer(Group G) : G(G)
{
    BigInt rand;
    // TODO: Is that random function secure?
    G.get_rand_bn(rand);
    s = BigInt(rand);
}

Point AuthenticationServer::sign(Point r) {
    return blind(r, s);
}