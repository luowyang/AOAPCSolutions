/**
 * Compound Words, UVa10391
**/

#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define index(c) (c-'a')

const int maxn = 240000, maxm = 26;
int trie[maxn][maxm] = {0}, N = 1;
vector<string> dict;    // dictionary
//map<int, int> vals;     // values of the trie, node# to string#
int vals[maxn] = {0};

void insert(int s) {
    int cur = 0, next;
    for (unsigned int i = 0; i < dict[s].length(); i++) {
        next = trie[cur][index(dict[s][i])];
        if (!next) { trie[cur][index(dict[s][i])] = N; next = N++; }
        cur = next;
    }
    // printf("DEBUG cur = %d\n", cur);
    if (!vals[cur]) vals[cur] = s;
    // cout << "DEBUG vals[cur] = " << dict[vals[cur]] << "\n"; 
}

void collect(int node, vector<int> &pre) {
    if (!node) return;
    if (vals[node]) pre.push_back(vals[node]);
    for (int i = 0; i < maxm; i++) collect(trie[node][i], pre);
}

void prefix(vector<int>& pre, int s) {
    int cur = 0;
    for (unsigned int i = 0; i < dict[s].length(); i++) {
        if (vals[cur]) pre.push_back(vals[cur]);
        cur = trie[cur][index(dict[s][i])];
        if (!cur) return;
    }
}

bool contains(const string& s) {
    int cur = 0;
    for (unsigned int i = 0; i < s.length(); i++) {
        cur = trie[cur][index(s[i])];
        if (!cur) return false;
    }
    return vals[cur];
}

void printStr(const vector<int> v) {
    for (auto t : v)
        cout << dict[t] << " ";
    cout << "\n";
}

void printTrie() {
    for (int i = 0; i < N; i++) {
        if (vals[i]) {
                cout << dict[vals[i]] << " ";
            cout << "\n";
        }
    }
}

int main() {
    string s;
    int k = 1;
    dict.push_back("THISSHOULDNOTAPPEAR");
    while (cin >> s) {
        dict.push_back(s);
        // cout << "DEBUG s = " << s << "\n";
        insert(k++);
        // printf("DEBUG N = %d, print trie:\n", N);
        // printTrie();
    }
    vector<int> pre, ans;
    for (unsigned int i = 1; i < dict.size(); i++) {
        pre.clear();
        prefix(pre, i);
        // printf("DEBUG pre of %s: ", dict[i].c_str()); printStr(pre);
        for (auto t : pre)
            if (contains(dict[i].substr(dict[t].length()))) { ans.push_back(i); break; }
    }
    for (auto t : ans) cout << dict[t] << "\n";
    return 0;
}