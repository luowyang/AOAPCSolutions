/**
 * Alignment of Code, UVa1593
**/

#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    vector<vector<string> > code;
    vector<unsigned int> len;
    string buf, s;
    while (getline(cin, buf)) {
        stringstream ss(buf);
        vector<string> line;
        for (unsigned int i = 0; ss >> s; i++) {
            if (len.size() <= i) len.push_back(s.length());
            else if (len[i] < s.length()) len[i] = s.length();
            line.push_back(s);
        }
        code.push_back(line);
    }
    for (auto &v : code) {
        for (unsigned int i = 0; i < v.size()-1; i++)
            cout << left << setw(len[i]) << v[i] << " ";
        cout << v[v.size()-1] << "\n";
    }
    return 0;
}