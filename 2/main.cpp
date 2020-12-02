#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, const char** argv) {
  cout << "Advent of Code Puzzle # 2" << endl;
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

  regex reg_pword("([0-9]+)-([0-9]+) ([A-Za-z]): (.*)");

  int good_a = 0;
  int good_b = 0;

  string latest;
  while (getline(ifilein, latest, '\n')) {
    smatch mr;
    auto matches = regex_match(latest, mr, reg_pword);
    auto pwd = mr[4].str();
    auto chr = mr[3].str()[0];
    int min = stoi(mr[1].str());
    int max = stoi(mr[2].str());

    int occur = count(pwd.begin(), pwd.end(), chr);
    if (occur >= min && occur <= max) {
      good_a++;
    }

    min--;
    max--;
    occur = 0;
    if (min < pwd.size() && pwd[min] == chr) {
      occur++;
    }
    if (max < pwd.size() && pwd[max] == chr) {
      occur++;
    }

    if (occur == 1) {
      good_b++;
    }
  }

  cout << "Total good (a): " << good_a << endl;
  cout << "Total good (b): " << good_b << endl;

  cout << "----------" << endl;
  return 0;
}