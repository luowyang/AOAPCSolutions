/**
 * Updating a Dictionary, UVa12504
**/

#include <vector>
#include <map>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;

void buildDict(const char* s, map<string, string>& dict) {
    unsigned int i, j, k;
    // printf("DEBUG s %s\n", s);
    if (!s[2]) return;
    for (i = 1; s[i]; i = k+1) {
        for (j = i+1; s[j] != ':'; j++);
        for (k = j+1; s[k] != '}' && s[k] != ','; k++);
        dict.insert({string(&s[i], j-i), string(&s[j+1], k-j-1)});
        // cout << "DEBUG " << string(&s[i], j-i) << " : " << string(&s[j+1], k-j-1) << "\n";
    }
}

void printAns(const vector<string>& ans, const char c) {
    bool first = true;
    for (auto &s : ans) {
        if (first) { cout << c; first = false; } else cout << ",";
        cout << s;
    }
    cout << "\n";
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        map<string, string> od, nd;
        vector<string> ans;
        bool same = true;
        char buf[200];
        scanf("%s", buf); buildDict(buf, od);
        scanf("%s", buf); buildDict(buf, nd);
        for (auto &nk : nd) if (!od.count(nk.first)) ans.push_back(nk.first);
        if (!ans.empty()) {
            printAns(ans, '+');
            same = false;
        }
        ans.clear();
        for (auto &ok : od) if (!nd.count(ok.first)) ans.push_back(ok.first);
        if (!ans.empty()) {
            printAns(ans, '-');
            same = false;
        }
        ans.clear();
        for (auto &ok : od) if (nd.count(ok.first) && nd[ok.first] != ok.second) ans.push_back(ok.first);
        if (!ans.empty()) {
            printAns(ans, '*');
            same = false;
        }
        if (same) cout << "No changes\n";
        cout << '\n';
    }
    return 0;
}