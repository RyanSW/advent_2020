#include <fstream>
#include <iostream>
#include <deque>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;


int main(int argc, const char** argv) {
    cout << "Advent of Code Puzzle # 9" << endl;
    cout << "----------" << endl;

    if (argc < 2) {
        cerr << "Input file is required." << endl;
        cout << "----------" << endl;
        return 1;
    }

    ifstream ifilein(argv[1]);

    if (!ifilein.is_open()) {
        cerr << "File could not be opened." << endl;
        cout << "----------" << endl;
        return 1;
    }

    // Start Challenge
    string latest;
    deque<long> numbers;
    vector<long> ctg_sum;
    long not_found;

    while (getline(ifilein, latest, '\n')) {
        long num = stol(latest);

        ctg_sum.push_back(num);

        if (numbers.size() < 25) {
            numbers.push_back(num);
            continue;
        }

        bool good = false;
        for (auto i1 = numbers.begin(); i1 != numbers.end(); i1++) {
            for (auto i2 = numbers.begin(); i2 != numbers.end(); i2++) {
                if (i1 == i2)
                    continue;

                if (*i1 + *i2 == num) {
                    good = true;
                    break;
                }
            }
            if (good) break;
        }

        if (!good)
            not_found = num;

        numbers.push_back(num);
        numbers.pop_front();
    }

    cout << "Number not found " << not_found << endl;

    int comps;
    for (auto fwd = ctg_sum.begin(); fwd != ctg_sum.end(); fwd++) {
        for (auto bwd = ctg_sum.rbegin(); bwd.base() != fwd; bwd++) {
            if (accumulate(fwd, bwd.base(), 0) == not_found) {
                auto mm = minmax_element(fwd, bwd.base());
                if (*mm.first == *mm.second)
                    continue;
                cout << "Sum of smallest and largest is " << (*(mm.first) + *(mm.second)) << endl;
            }
        }
    }

    cout << "----------" << endl;
    return 0;
}
