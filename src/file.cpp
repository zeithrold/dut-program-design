#include "file.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

bool write_file(string target_filename, vector<string> text) {
    ofstream outfile;
    outfile.open(target_filename, ios::out | ios::trunc);
    //locale mylocale("zh_CN");
    //outfile.imbue(mylocale);
    if (!outfile.is_open()) {
        return false;
    }
    for (const auto &item: text) {
        outfile << item << "\n";
    }
    outfile.close();
    return true;
}

vector<string> read_file(string target_filename) {
    ifstream infile;
    vector<string> result;
    infile.open(target_filename, ios::in);
    //locale mylocale("zh_CN");
    //infile.imbue(mylocale);
    if (!infile.is_open()) {
        return result;
    }
    string line;
    bool first_line = true;
    while (getline(infile, line)) { // getline(fstream, string) ignores "\n"
        if (first_line) {
            first_line = false;
            continue;
        }
        result.push_back(line);
    }
    return result;
}
