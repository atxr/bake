#pragma once
#include "core/Core.hpp"

class AuthenticationServer
{
public:
    Point sign(Point r);

private:
    Group G;
    BigInt s;
};