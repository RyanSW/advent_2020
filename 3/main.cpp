#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, const char** argv) {
  cout << "Advent of Code Puzzle # 3" << endl;
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
  int index_11 = 0;
  int index_31 = 0;
  int index_51 = 0;
  int index_71 = 0;
  int index_12 = 0;
  int skip_12 = 0;

  unsigned int count_11 = 0;
  unsigned int count_31 = 0;
  unsigned int count_51 = 0;
  unsigned int count_71 = 0;
  unsigned int count_12 = 0;

  while (getline(ifilein, latest, '\n')) {
    if (latest[index_11] == '#')
      count_11++;
    index_11 = (index_11 + 1) % latest.size();

    if (latest[index_31] == '#')
      count_31++;
    index_31 = (index_31 + 3) % latest.size();

    if (latest[index_51] == '#')
      count_51++;
    index_51 = (index_51 + 5) % latest.size();

    if (latest[index_71] == '#')
      count_71++;
    index_71 = (index_71 + 7) % latest.size();

    if (skip_12) {
      skip_12 = 0;
    } else {
      skip_12 = 1;
      if (latest[index_12] == '#')
        count_12++;
      index_12 = (index_12 + 1) % latest.size();
    }
  }

  cout << "Trees 1-1 " << count_11 << endl;
  cout << "Trees 3-1 " << count_31 << endl;
  cout << "Trees 5-1 " << count_51 << endl;
  cout << "Trees 7-1 " << index_71 << endl;
  cout << "Trees 1-2 " << count_12 << endl;

  cout << "Product "
       << ((long)count_11 * count_31 * count_51 * count_71 * count_12) << endl;

  cout << "----------" << endl;
  return 0;
}