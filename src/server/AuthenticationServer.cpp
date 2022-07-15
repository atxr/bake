#include "AuthenticationServer.hpp"

AuthenticationServer::AuthenticationServer(Group ECGroup) : ECGroup(ECGroup)
{
    // TODO: Is that random function secure?
    ECGroup.get_rand_bn(k);
}

Group *AuthenticationServer::getGroup() { return &ECGroup; }

Point AuthenticationServer::sign(Point B)
{
    return blind(B, k);
}