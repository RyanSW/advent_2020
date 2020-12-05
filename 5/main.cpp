#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, const char** argv) {
  cout << "Advent of Code Puzzle # 5" << endl;
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
  vector<int> seats;
  int max_seatid = 0;

  while (getline(ifilein, latest, '\n')) {
    auto row_str = latest.substr(0, 7);
    int row_num = 0;
    for (auto r_itr = row_str.begin(); r_itr != row_str.end(); r_itr++) {
      row_num <<= 1;
      if (*r_itr == 'B')
        row_num |= 1;
    }
    auto col_str = latest.substr(7, 3);
    int col_num = 0;
    for (auto c_itr = col_str.begin(); c_itr != col_str.end(); c_itr++) {
      col_num <<= 1;
      if (*c_itr == 'R')
        col_num |= 1;
    }

    int seat_id = row_num * 8 + col_num;
    if (seat_id > max_seatid) {
      max_seatid = seat_id;
    }
    seats.push_back(seat_id);
  }

  cout << "Max Seat ID is " << max_seatid << endl;

  sort(seats.begin(), seats.end());

  for (auto seat_itr = seats.begin(); seat_itr != seats.end() - 1; seat_itr++) {
    int a = *seat_itr;
    int b = *(seat_itr + 1);
    if (b - a == 2) {
      cout << "Potential seat at " << a + 1 << endl;
    }
  }

  cout << "----------" << endl;
  return 0;
}