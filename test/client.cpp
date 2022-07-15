#include <iostream>
#include <openssl/ec.h>
#include "client/Client.hpp"

using namespace std;

int main()
{
    Group ECGroup;
    // Init the servers
    AuthenticationServer as(ECGroup);
    ComputationServer cs(as);

    // Create a client
    Client c(cs);
    if (!c.init())
    {
        cout << "Error during init" << endl;
        exit(1);
    }

    if (!c.enroll(FuzzyVault()))
    {
        cout << "Enrollment failed" << endl;
        exit(1);
    }
    cout << "Enrollment successful!" << endl;
    
    if (!c.verify(Query()))
    {
        cout << "Verify: Query failed" << endl;
        exit(1);
    }
    cout << "Verification successful" << endl;

    return 0;
}