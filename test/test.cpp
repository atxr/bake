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

bool testOne(string ref, string query)
{
    // Initialisation
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
    if (!c.enroll(getMinutiaeView(ref), false))
    {
        return false;
    }

    // Verification
    return c.verify(getMinutiaeView(query), false);
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
    int aMax(434);
    int bMax(9);
    int cMax(11);

    int mated(0);
    int nonmated(0);
    int error(0);

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

                try
                {
                    if (testOne(path + imageName, path + query))
                        mated++;
                }
                catch (int e)
                {
                    if (e == 1)
                    {
                        cout << "Error: Permutation::eval failed" << endl;
                    }
                    error++;
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
                    if (testOne(path + imageName, path + query))
                        nonmated++;
                }
                catch (int e)
                {
                    if (e == 1)
                    {
                        cout << "Error: Permutation::eval failed" << endl;
                    }
                    error++;
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
    cout << "Test finished, with " << n * 2 << " different key exchanges." << endl;
    cout << "Results: mated | nonmated" << endl;
    cout << "Success: "
         << mated << " / " << counter << " | "
         << nonmated << "/" << counter << endl;
    cout << "Failure: "
         << counter - mated - error << "/" << counter << " | "
         << counter - nonmated - error << "/" << counter << endl;
    cout << "Errors: "
         << mated << "/" << counter << " | "
         << nonmated << "/" << counter << endl;

    return 0;
}