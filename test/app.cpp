#include <iostream>
#include <openssl/ec.h>
#include "core/Core.hpp"

using namespace std;

int main() {
    cout << "Hello, World!" << std::endl;
    Group G;
    BigInt i;
    G.get_rand_bn(i);

    Point p = Core::hashToCurve(G, i);

    // TODO: ERROR HERE when destructing the group G
    return 0;
}