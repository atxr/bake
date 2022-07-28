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
struct Result
{
    int init, enroll, verify, full, st;
    Result()
    {
        init = enroll = verify = full = st = -1;
    }

    Result(int i)
    {
        init = i;
        enroll = verify = full = st = -1;
    }

    Result(int i, int e, int v, int f, int s)
    {
        init = i;
        enroll = e;
        verify = v;
        full = f;
        st = s;
    }
};

int median(vector<int> &v)
{
    if (v.empty())
    {
        return 0;
    }
    auto n = v.size() / 2;
    nth_element(v.begin(), v.begin() + n, v.end());
    auto med = v[n];
    if (!(v.size() & 1))
    { // If the set size is even
        auto max_it = max_element(v.begin(), v.begin() + n);
        med = (*max_it + med) / 2.0;
    }
    return med;
}

Result testOne(string ref, string query)
{
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
        return Result();
    }

    auto stop = chrono::high_resolution_clock::now();
    int init = chrono::duration_cast<chrono::milliseconds>(stop - start).count();

    // Enrollment

    start = chrono::high_resolution_clock::now();
    if (!c.enroll(getMinutiaeView(ref), false))
    {
        return Result(init);
    }

    stop = chrono::high_resolution_clock::now();
    int enroll = chrono::duration_cast<chrono::milliseconds>(stop - start).count();

    // Verification

    start = chrono::high_resolution_clock::now();
    int st = c.verify(getMinutiaeView(query), false) ? 1 : 0;

    stop = chrono::high_resolution_clock::now();
    int verify = chrono::duration_cast<chrono::milliseconds>(stop - start).count();
    int full = chrono::duration_cast<chrono::milliseconds>(stop - startFull).count();
    return Result(init, enroll, verify, full, st);
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

    vector<int> mated[5];
    vector<int> nonmated[5];
    Result res;

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
                string b = imageName.substr(8, 1);
                string c = imageName.substr(10, 2);
                bool pad = 1;

                if (c.find(".") != string::npos)
                {
                    pad = 0;
                    c = c.substr(0, 1);
                }

                string query = imageName.substr(0, 10) +
                               to_string(1 + stoi(c) % cMax) +
                               imageName.substr(11 + pad);

                cout << counter << "/" << n << ": " << path << imageName << " VS " << path << query << endl;
                res = testOne(path + imageName, path + query);

                mated[0].push_back(res.init);
                mated[1].push_back(res.enroll);
                mated[2].push_back(res.verify);
                mated[3].push_back(res.full);
                mated[4].push_back(res.st);

                query = imageName.substr(0, 8) +
                        to_string(1 + stoi(b) % bMax) +
                        imageName.substr(9);

                cout << counter << "/" << n << ": " << path << imageName << " VS " << path << query << endl;
                res = testOne(path + imageName, path + query);

                nonmated[0].push_back(res.init);
                nonmated[1].push_back(res.enroll);
                nonmated[2].push_back(res.verify);
                nonmated[3].push_back(res.full);
                nonmated[4].push_back(res.st);

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
         << count(mated[4].begin(), mated[4].end(), 1) * 100 / mated[4].size() << "% | "
         << count(nonmated[4].begin(), nonmated[4].end(), 1) * 100 / nonmated[4].size() << "%" << endl;
    cout << "Failure: "
         << count(mated[4].begin(), mated[4].end(), 0) * 100 / mated[4].size() << "% | "
         << count(nonmated[4].begin(), nonmated[4].end(), 0) * 100 / nonmated[4].size() << "%" << endl;
    cout << "Errors: " 
         << count(mated[4].begin(), mated[4].end(), -1) * 100 / mated[4].size() << "% | "
         << count(nonmated[4].begin(), nonmated[4].end(), -1) * 100 / nonmated[4].size() << "%" << endl;

    cout << endl;
    cout << "Times: mated | nonmated" << endl;
    cout << "Init: " << median(mated[0]) << "ms | " << median(nonmated[0]) << "ms" << endl;
    cout << "Enroll: " << median(mated[1]) << "ms | " << median(nonmated[1]) << "ms" << endl;
    cout << "Verify: " << median(mated[2]) << "ms | " << median(nonmated[2]) << "ms" << endl;
    cout << "Full: " << median(mated[3]) << "ms | " << median(nonmated[3]) << "ms" << endl;

    return 0;
}