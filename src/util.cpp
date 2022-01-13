#include <vector>
#include <string>
#include <time.h>
#include "util.h"

using namespace std;

vector<string> split_str(string s, string pattern) {
    vector<string> result;
    if (s.empty()) {
        return result;
    }
    string work_string = s + pattern;
    int pos = (int)work_string.find(pattern);
    int size = (int)work_string.size();
    while (pos != string::npos) {
        string item = work_string.substr(0, pos);
        result.push_back(item);
        work_string = work_string.substr(pos + 1, size);
        pos = work_string.find(pattern);
    }
    return result;
}

string convert_to_local_time(time_t t) {
    tm* local_time = localtime(&t);
    char result[64];
    strftime(result, sizeof(result), "%Y-%m-%d %H:%M:%S", local_time);
    return result;
}
