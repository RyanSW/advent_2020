#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <bitset>
#include <map>

using namespace std;

enum opcode {
    acc,
    jmp,
    nop
};

int main(int argc, const char** argv) {
    cout << "Advent of Code Puzzle # 8" << endl;
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
    vector<pair<opcode, int>> opcodes;
    map<int, bool> visited;

    while (getline(ifilein, latest, '\n')) {
        auto opcode = latest.substr(0, 3);
        int arg = stoi(latest.substr(4));

        if (opcode == "acc")
            opcodes.push_back(pair(acc, arg));
        if (opcode == "jmp")
            opcodes.push_back(pair(jmp, arg));
        if (opcode == "nop")
            opcodes.push_back(pair(nop, arg));
    }

    int accumulator = 0;
    int iptr = 0;

    while (!visited[iptr]) {
        visited[iptr] = true;
        switch (opcodes[iptr].first) {
        case nop:
            iptr++;
            break;

        case jmp:
            iptr += opcodes[iptr].second;
            break;

        case acc:
            accumulator += opcodes[iptr].second;
            iptr++;
            break;
        }
    }

    cout << "Acc is normally " << accumulator << endl;

    for (auto i = opcodes.begin(); i != opcodes.end(); i++) {
        auto restore = i->first;
        switch (i->first) {
        case nop:
            i->first = jmp;
            break;
        case jmp:
            i->first = nop;
            break;
        case acc:
            continue;
        }

        accumulator = 0;
        iptr = 0;
        visited.clear();

        while (!visited[iptr] && iptr < opcodes.size()) {
            visited[iptr] = true;
            switch (opcodes[iptr].first) {
            case nop:
                iptr++;
                break;

            case jmp:
                iptr += opcodes[iptr].second;
                break;

            case acc:
                accumulator += opcodes[iptr].second;
                iptr++;
                break;
            }
        }

        if (iptr >= opcodes.size()) {
            cout << "Exceeded by " << (opcodes.size() + 1 - iptr) << ", acc is " << accumulator << endl;
        }

        i->first = restore;
    }


    cout << "----------" << endl;
    return 0;
}
