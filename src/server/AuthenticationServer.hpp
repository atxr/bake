#pragma once
#include "core/Core.hpp"

class AuthenticationServer
{
public:
    AuthenticationServer(Group g);

private:
    Group G;
    BigInt s;
};