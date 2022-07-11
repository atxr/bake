#include <iostream>
#include <openssl/ec.h>
#include "client/Client.hpp"

using namespace std;

int main() {
    Group G;
    // Init the servers
    AuthenticationServer as;
    ComputationServer cs(as);

    // Create a client
    Client c(0, FuzzyVault()); 
    if (c.enroll(cs)) {
        cout << "Enrollment successful" << endl;
    }
    else {
        cout << "nani" << endl;
    }
    return 0;
}