#pragma once
#include "core/Core.hpp"

class AuthenticationServer
{
public:
    AuthenticationServer(Group G);
    Group* getGroup();
    Point sign(Point r);

private:
    Group G;
    BigInt s;
};