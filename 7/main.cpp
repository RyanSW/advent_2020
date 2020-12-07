#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <vector>

using namespace std;

bool can_hold(int id,
              int search_id,
              const map<int, vector<pair<int, int>>>& contents,
              map<int, bool>& possible) {
  auto save_time = possible.find(id);
  if (save_time != possible.end()) {
    return save_time->second;
  }

  for (auto cnts : contents.at(id)) {
    if (can_hold(cnts.first, search_id, contents, possible) ||
        cnts.first == search_id) {
      possible[id] = true;
      return true;
    }
  }

  possible[id] = false;
  return false;
}

int bag_count(int id,
              const map<int, vector<pair<int, int>>>& contents,
              map<int, int>& known) {
  auto save_time = known.find(id);
  if (save_time != known.end()) {
    return save_time->second;
  }

  int bags = 1;
  for (auto cnts : contents.at(id)) {
    bags += cnts.second * bag_count(cnts.first, contents, known);
  }

  known[id] = bags;
  return bags;
}

int main(int argc, const char** argv) {
  cout << "Advent of Code Puzzle # 7" << endl;
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
  int last_id = 0;
  map<string, int> id_pairs;
  map<int, vector<pair<int, int>>> contents;

  regex overall("([a-z ]+) bags contain ([^.]*.)");
  regex inside("([0-9]+) ([a-z ]+) bag[s]?[,.][ ]?");

  smatch m_overall;
  smatch m_inside;

  while (getline(ifilein, latest, '\n')) {
    if (regex_match(latest, m_overall, overall)) {
      auto i = m_overall[2].str();
      vector<pair<int, int>> this_content;

      if (id_pairs.find(m_overall[1].str()) == id_pairs.end()) {
        id_pairs[m_overall[1].str()] = last_id++;
      }

      while (regex_search(i, m_inside, inside)) {
        if (id_pairs.find(m_inside[2].str()) == id_pairs.end()) {
          id_pairs[m_inside[2].str()] = last_id++;
        }

        this_content.push_back(
            pair(id_pairs[m_inside[2].str()], stoi(m_inside[1].str())));

        i = m_inside.suffix().str();
      }

      contents[id_pairs[m_overall[1].str()]] = this_content;
    } else {
      cerr << "No match for overall regex on " << latest << endl;
    }
  }

  map<int, bool> possible;
  map<int, int> known;

  int search = id_pairs["shiny gold"];
  int can_holds = 0;
  for (auto x : id_pairs) {
    if (can_hold(x.second, search, contents, possible))
      can_holds++;
  }

  cout << can_holds << endl;
  cout << (bag_count(search, contents, known) - 1) << endl;

  cout << "----------" << endl;
  return 0;
}
