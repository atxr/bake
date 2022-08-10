#include <iostream>
#include <openssl/ec.h>
#include "client/Client.hpp"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Error. Not enough arguments" << endl;
        cout << "Usage: bake <path to reference image> <path to query image>" << endl;
        exit(1);
    }

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
    // permutation::eval may throw an error
    try
    {
        if (!c.verify(getMinutiaeView(argv[2])))
        {
            cout << "Verify: Query failed" << endl;
            exit(1);
        }
    }
    catch (int e)
    {
        if (e == 1)
            cout << "Error: Caught invalid permutation::eval" << endl;
        else
            cout << "Caught " << e << endl;
        exit(e);
    }
    cout << "Verification successful" << endl;

    return 0;
}