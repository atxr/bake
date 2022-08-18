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
#include <iomanip>
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
    auto stop1 = chrono::high_resolution_clock::now();
    if (!c.enroll(view, k, false))
    {
        throw 3;
    }

    // Verification
    bool st = c.verify(getMinutiaeView(query), k, false);

    auto stop = chrono::high_resolution_clock::now();
    int fullTime = chrono::duration_cast<chrono::milliseconds>(stop - start).count();
    int viewTime = chrono::duration_cast<chrono::microseconds>(stop1 - start1).count();
    ofstream OutFull("out/full_" + to_string(k) + ".chrono", ios_base::app);
    OutFull << fullTime << endl;
    OutFull.close();

    ofstream OutView("out/view_" + to_string(k) + ".chrono", ios_base::app);
    OutView << viewTime << endl;
    OutView.close();

    return st;
}

void testOnek(string path, int n, int k)
{
    int aMax(330);
    int bMax(3);
    vector<int> aDone;

    int mated(0);
    int nonmated(0);
    int error1(0);
    int error2(0);
    int count1 = 0;
    int count2 = 0;

    DIR *dir;
    struct dirent *ent;
    int counter(0);
    if ((dir = opendir(path.c_str())) != NULL)
    {
        while ((ent = readdir(dir)) != NULL && counter < n)
        {
            string imageName(ent->d_name);
            if (imageName.find(".pgm", 0) != string::npos)
            {
                string a = imageName.substr(0, 3);
                string b = imageName.substr(4, 1);

                if (find(aDone.begin(), aDone.end(), stoi(a)) == aDone.end())
                {
                    cout << "Test individual " << a << endl;
                    for (int i = 1; i < bMax; i++)
                    {
                        stringstream ss;
                        ss << a << "_" << to_string((i + stoi(b)) % bMax) << ".pgm";
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
                            count1++;
                            continue;
                        }
                        count1++;
                    }

                    for (int i = 0; i < 7; i++)
                    {
                        int r = rand() % (aMax - 1) + 1;

                        stringstream ss;
                        ss = stringstream();
                        ss << a << "_" << i % bMax << ".pgm";
                        string probe = ss.str();

                        ss = stringstream();
                        string ind = to_string((r + stoi(a)) % aMax);
                        for (int z = ind.size(); z < 3; z++)
                        {
                            ind = "0" + ind;
                        }
                        ss << ind << "_0.pgm";
                        string query = ss.str();

                        cout << counter << "/" << n << ": " << path << probe << " VS " << path << query << endl;

                        // reorder may throw exception if permutation::eval fails
                        try
                        {
                            if (testOne(path + probe, path + query, k))
                                nonmated++;
                        }
                        catch (int e)
                        {
                            cout << "Caught: " << e << endl;
                            error2++;
                            count2++;
                            continue;
                        }
                        count2++;
                    }

                    counter++;
                    aDone.push_back(stoi(a));
                }
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
    ofstream Out("out/" + to_string(k) + ".res");
    Out << "Test finished, with " << counter << " different probe individual for k = " << k << endl;
    Out << mated << "/" << count1 << endl
        << nonmated << "/" << count2 << endl;
    Out << count1 - mated - error1 << "/" << count1 << endl
        << count2 - nonmated - error2 << "/" << count2 << endl;
    Out << error1 << "/" << count1 << endl
        << error2 << "/" << count2 << endl;
    Out.close();
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

    auto ks = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
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
