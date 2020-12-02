#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

static const unsigned int compare = 2020;

int main(int argc, const char** argv) {
  vector<unsigned int> numbers;
  vector<pair<unsigned int, unsigned int>> small_sums;

  cout << "Advent of Code Puzzle # 1" << endl;
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

  unsigned int latest;
  while (ifilein >> latest) {
    numbers.push_back(latest);
  }

  sort(numbers.begin(), numbers.end());

  {  // Part 1
    auto fwd = numbers.begin();
    auto bwd = numbers.rbegin();

    while (fwd != numbers.end() && bwd != numbers.rend()) {
      while (*fwd + *bwd > compare && bwd != numbers.rend()) {
        bwd++;
      }
      if (*fwd + *bwd == compare) {
        cout << "Found " << *fwd << " * " << *bwd << " = " << (*fwd * *bwd)
             << endl;
      }
      fwd++;
    }
  }

  {  // Part 2 A (Get Small Sums)

    auto fwd = numbers.begin();
    auto bwd = numbers.rbegin();
    while (fwd != numbers.end() && bwd != numbers.rend()) {
      while (*fwd + *bwd >= compare && bwd != numbers.rend()) {
        bwd++;
      }

      if (*fwd + *bwd < compare) {
        auto bwd2 = bwd;
        while (bwd2 != numbers.rend() && *bwd2 > *fwd) {
          small_sums.push_back(pair(*fwd, *bwd2));
          bwd2++;
        }
      }

      fwd++;
    }

    sort(small_sums.begin(), small_sums.end(),
         [](pair<unsigned int, unsigned int> a,
            pair<unsigned int, unsigned int> b) -> bool {
           return (a.first + a.second) < (b.first + b.second);
         });
  }

  {  // Part 2 B
    auto fwd = small_sums.begin();
    auto bwd = numbers.rbegin();

    while (fwd != small_sums.end() && bwd != numbers.rend()) {
      unsigned int sum = fwd->first + fwd->second;
      while (sum + *bwd > compare && bwd != numbers.rend()) {
        bwd++;
      }

      if (sum + *bwd == compare) {
        cout << "Found " << fwd->first << " * " << fwd->second << " * " << *bwd
             << " = " << (fwd->first * fwd->second * *bwd) << endl;
      }

      fwd++;
    }
  }

  cout << "----------" << endl;
  return 0;
}