#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, const char** argv) {
  cout << "Advent of Code Puzzle # 6" << endl;
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
  bitset<26> mask_any(0);
  bitset<26> mask_all(0);
  mask_all.set();
  int sum_any = 0;
  int sum_all;

  while (getline(ifilein, latest, '\n')) {
    if (latest.empty()) {
      sum_any += mask_any.count();
      sum_all += mask_all.count();
      mask_any.reset();
      mask_all.set();
      continue;
    }
    bitset<26> mask(0);

    for (auto chr : latest) {
      mask[chr - 'a'] = 1;
    }
    mask_any |= mask;
    mask_all &= mask;
  }
  sum_any += mask_any.count();
  sum_all += mask_all.count();

  cout << "Any yes: " << sum_any << endl;
  cout << "All yes: " << sum_all << endl;

  cout << "----------" << endl;
  return 0;
}
