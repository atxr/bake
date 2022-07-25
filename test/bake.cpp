#include <iostream>
#include <openssl/ec.h>
#include "client/Client.hpp"

using namespace std;

int main(int argc, char** argv)
{
    // Initialisation

    cout << "Init" << endl;
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
    cout << "Init successful" << endl
         << endl;

    // Enrollment

    cout << "Enrollment" << endl;
    if (!c.enroll(getMinutiaeView(argv[1])))
    {
        cout << "Enrollment failed" << endl;
        exit(1);
    }
    cout << "Enrollment successful!" << endl
         << endl;

    // Verification

    cout << "Verification" << endl;
    if (!c.verify(getMinutiaeView(argv[2])))
    {
        cout << "Verify: Query failed" << endl;
        exit(1);
    }
    cout << "Verification successful" << endl;

    return 0;
}