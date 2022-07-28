#include <iostream>
#include <openssl/ec.h>
#include "client/Client.hpp"
#include <chrono>

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
    auto startFull = chrono::high_resolution_clock::now();

    auto start = chrono::high_resolution_clock::now();
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

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Init timer: " << duration.count() << "ms" << endl;

    // Enrollment

    start = chrono::high_resolution_clock::now();
    if (!c.enroll(getMinutiaeView(argv[1]), false))
    {
        cout << "Enrollment failed" << endl;
        exit(1);
    }

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Enrollment timer: " << duration.count() << "ms" << endl;

    // Verification

    start = chrono::high_resolution_clock::now();
    if (!c.verify(getMinutiaeView(argv[2]), false))
    {
        cout << "Verify: Query failed" << endl;
    }

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    auto durationFull = chrono::duration_cast<chrono::milliseconds>(stop - startFull);
    cout << "Verification timer: " << duration.count() << "ms" << endl;
    cout << "Full timer: " << durationFull.count() << "ms" << endl;
    return 0;
}