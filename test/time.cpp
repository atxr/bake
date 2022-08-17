/**
 * @file time.cpp
 * @author Alexandre TULLOT (Alexandre.TULLOT@student.isae-supaero.fr)
 * @brief Test the time performances of the protocol
 * @date 2022-07-28
 *
 * @copyright Copyright (c) 2022
 *
 * This test was designed with the mcyt fingerprint dataset.
 */

#include <iostream>
#include "client/Client.hpp"
#include <chrono>
#include <dirent.h>
#include <vector>
#include <algorithm>

using namespace std;

bool testOne(string ref, string query, int k)
{
    // Initialisation
    auto start = chrono::high_resolution_clock::now();

    Group ECGroup;
    // Init the servers
    AuthenticationServer as(ECGroup);
    ComputationServer cs(as);

    // Create a client
    Client c(cs);
    if (!c.init())
    {
        throw 2;
    }

    // Enrollment
    auto start1 = chrono::high_resolution_clock::now();
    MinutiaeView view = getMinutiaeView(ref);
    auto stop = chrono::high_resolution_clock::now();
    if (!c.enroll(view, k, false))
    {
        throw 3;
    }

    // Verification
    bool st = c.verify(getMinutiaeView(query), k, false);

    stop = chrono::high_resolution_clock::now();
    int fullTime = chrono::duration_cast<chrono::milliseconds>(stop - start).count();
    ofstream OutFull("out/full_" + to_string(k) + ".chrono", ios_base::app);
    OutFull << fullTime << endl;
    OutFull.close();

    int viewTime = chrono::duration_cast<chrono::microseconds>(stop - start1).count();
    ofstream OutView("out/view_" + to_string(k) + ".chrono", ios_base::app);
    OutView << viewTime << endl;
    OutView.close();

    return st;
}

void testOnek(string path, int n, int k)
{
    int aMax(434);
    int bMax(9);
    int cMax(11);

    int mated(0);
    int nonmated(0);
    int error1(0);
    int error2(0);

    DIR *dir;
    struct dirent *ent;
    int counter = 0;
    if ((dir = opendir(path.c_str())) != NULL)
    {
        while ((ent = readdir(dir)) != NULL && counter < n)
        {
            string imageName(ent->d_name);
            if (imageName.find(".pgm", 0) != string::npos)
            {
                stringstream ss;
                string b = imageName.substr(8, 1);
                string c = imageName.substr(10, 2);
                bool pad = 1;

                if (c.find(".") != string::npos)
                {
                    pad = 0;
                    c = c.substr(0, 1);
                }

                ss << imageName.substr(0, 10) << to_string((1 + stoi(c)) % cMax) << imageName.substr(11 + pad);
                string query = ss.str();

                cout << counter << "/" << n << ": " << path << imageName << " VS " << path << query << endl;

                // reorder may throw exception if permutation::eval fails
                try
                {
                    if (testOne(path + imageName, path + query, k))
                        mated++;
                }
                catch (int e)
                {
                    cout << "Caught: " << e << endl;
                    error1++;
                    counter++;
                    continue;
                }

                ss = stringstream();
                ss << imageName.substr(0, 8) << to_string((2 + stoi(b)) % bMax) << imageName.substr(9);
                query = ss.str();

                cout << counter << "/" << n << ": " << path << imageName << " VS " << path << query << endl;

                // reorder may throw exception if permutation::eval fails
                try
                {
                    if (testOne(path + imageName, path + query, k))
                        nonmated++;
                }
                catch (int e)
                {
                    cout << "Caught: " << e << endl;
                    error2++;
                    counter++;
                    continue;
                }

                counter++;
            }
        }
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        perror("");
        exit(EXIT_FAILURE);
    }

    cout << endl;
    cout << "Test finished, with " << counter * 2 << " different key exchanges." << endl;
    cout << "Results: mated | nonmated" << endl;
    cout << "Success: "
         << mated << "/" << counter << " | "
         << nonmated << "/" << counter << endl;
    cout << "Failure: "
         << counter - mated - error1 << "/" << counter << " | "
         << counter - nonmated - error2 << "/" << counter << endl;
    cout << "Errors: "
         << error1 << "/" << counter << " | "
         << error2 << "/" << counter << endl;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Error. Not enough arguments" << endl;
        cout << "Usage: bake <path to mcyt dp pgm images> <number of images for the test>" << endl;
        exit(1);
    }

    string path = argv[1];
    int n = stoi(argv[2]);

    auto ks = {8, 9, 10, 11, 12};
    for (int k : ks)
    {
        cout << endl
             << "Test for k = " << k << endl
             << endl;
        testOnek(path, n, k);
        cout << endl
             << "--------------------------------------------------------------" << endl;
    }

    return 0;
}
