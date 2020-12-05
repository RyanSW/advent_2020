#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

using namespace std;

struct passport {
  string byr;
  string iyr;
  string eyr;
  string hgt;
  string hcl;
  string ecl;
  string pid;
  string cid;
  union {
    unsigned int has_mask;
    struct {
      unsigned int byr : 1, iyr : 1, eyr : 1, hgt : 1, hcl : 1, ecl : 1,
          pid : 1, cid : 1;
    } has;
  };
  union {
    unsigned int valid_mask;
    struct {
      unsigned int byr : 1, iyr : 1, eyr : 1, hgt : 1, hcl : 1, ecl : 1,
          pid : 1;
    } valid;
  };
};

int main(int argc, const char** argv) {
  cout << "Advent of Code Puzzle # 4" << endl;
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
  string build;
  vector<string> passports;

  while (getline(ifilein, latest, '\n')) {
    if (latest.empty()) {
      passports.push_back(build);
      build.clear();
    } else {
      build += latest + ' ';
    }
  }
  // Add the last one with no blank line after
  if (!build.empty())
    passports.push_back(build);

  vector<passport> final_passports;

  regex valid_yr("^([0-9]{4})$");
  regex valid_hgt("^([0-9]+)(in|cm)$");
  regex valid_hcl("^#([0-9a-f]{6})$");
  regex valid_ecl("^(amb|blu|brn|gry|grn|hzl|oth)$");
  regex valid_pid("^([0-9]{9})$");

  // Read all of the passports
  for (auto passport_str : passports) {
    vector<string> build_strs;
    string b2;
    for (auto chr = passport_str.begin(); chr != passport_str.end(); chr++) {
      if (*chr == '\n' || *chr == ' ') {
        if (!b2.empty())
          build_strs.push_back(b2);
        b2.clear();
        continue;
      }

      b2 += *chr;
    }

    if (!b2.empty())
      build_strs.push_back(b2);

    passport this_passport = {};

    for (auto build_str : build_strs) {
      string field = build_str.substr(0, 3);
      string data = build_str.substr(4);
      smatch matches;

      if (field == "byr") {
        this_passport.byr = data;
        this_passport.has.byr = 1;
        if (regex_match(data, matches, valid_yr)) {
          int byr = stoi(matches[1]);
          if (byr >= 1920 && byr <= 2002)
            this_passport.valid.byr = 1;
        }
        continue;
      }

      if (field == "iyr") {
        this_passport.iyr = data;
        this_passport.has.iyr = 1;
        if (regex_match(data, matches, valid_yr)) {
          int iyr = stoi(matches[1]);
          if (iyr >= 2010 && iyr <= 2020)
            this_passport.valid.iyr = 1;
        }
        continue;
      }

      if (field == "eyr") {
        this_passport.eyr = data;
        this_passport.has.eyr = 1;
        if (regex_match(data, matches, valid_yr)) {
          int eyr = stoi(matches[1]);
          if (eyr >= 2020 && eyr <= 2030)
            this_passport.valid.eyr = 1;
        }
        continue;
      }

      if (field == "hgt") {
        this_passport.hgt = data;
        this_passport.has.hgt = 1;
        if (regex_match(data, matches, valid_hgt)) {
          int hgt = stoi(matches[1]);
          if (matches[2] == "cm" && hgt >= 150 && hgt <= 193)
            this_passport.valid.hgt = 1;
          if (matches[2] == "in" && hgt >= 59 && hgt <= 76)
            this_passport.valid.hgt = 1;
        }
        continue;
      }

      if (field == "hcl") {
        this_passport.hcl = data;
        this_passport.has.hcl = 1;
        if (regex_match(data, matches, valid_hcl)) {
          this_passport.valid.hcl = 1;
        }
        continue;
      }

      if (field == "ecl") {
        this_passport.ecl = data;
        this_passport.has.ecl = 1;
        if (regex_match(data, matches, valid_ecl)) {
          this_passport.valid.ecl = 1;
        }
        continue;
      }

      if (field == "pid") {
        this_passport.pid = data;
        this_passport.has.pid = 1;
        if (regex_match(data, matches, valid_pid)) {
          this_passport.valid.pid = 1;
        }
        continue;
      }

      if (field == "cid") {
        this_passport.cid = data;
        this_passport.has.cid = 1;
        continue;
      }

      cerr << "Unrecognized field name " << field << endl;
    }

    final_passports.push_back(this_passport);
  }

  int count_fields = 0;
  int count_data = 0;

  for (auto p : final_passports) {
    if (p.has_mask == 255 || p.has_mask == 127) {
      count_fields++;
    }
    if (p.valid_mask == 127) {
      count_data++;
    }
  }

  cout << "Valid Fields: " << count_fields << endl;
  cout << "Valid Data: " << count_data << endl;

  cout << "----------" << endl;
  return 0;
}