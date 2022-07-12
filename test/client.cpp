#include <iostream>
#include <openssl/ec.h>
#include "client/Client.hpp"

using namespace std;

int main() {
    Group G;
    // Init the servers
    AuthenticationServer as(G);
    ComputationServer cs(as);

    // Create a client
    Client c(cs); 
    if (!c.init()) {
        cout << "Error during init" << endl;
        exit(1);
    }
    if (!c.enroll(FuzzyVault())) {
        cout << "Enrollment failed" << endl;
    }
    cout << "Enrollment successful!" << endl;
    return 0;
}