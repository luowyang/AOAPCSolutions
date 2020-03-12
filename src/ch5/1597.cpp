/**
 * Searching the Web, UVa1597
**/

#include <set>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define SIN 0
#define AND 1
#define OR 2
#define NOT 3

map<string, map<int, set<int> > > ind;
vector<vector<string> > dat;

void buildIndex(const string &s, int k, int i) {
    unsigned int p, q;
    string t;
    for (p = 0; ; p = q) {
        while (p < s.length() && !isalpha(s[p])) p++;
        if (p == s.length()) break;
        for (q = p+1; q < s.length() && isalpha(s[q]); q++);
        t = s.substr(p, q-p);
        // cout << "DEBUG t: " << t << "\n";
        for (unsigned int j = 0; j < t.length(); j++) t[j] = tolower(t[j]);
        if (!ind.count(t)) ind.insert({t, map<int, set<int> >()});
        if (!ind[t].count(k)) ind[t].insert({k, set<int>()});
        ind[t][k].insert(i);
    }
}

int parseQuery(string &s, vector<string>& keys) {
    unsigned int p = 0, q;
    int type = SIN;
    while (!isalpha(s[p])) p++;
    if (s[p] == 'N') { type = NOT; p += 3; while (!isalpha(s[p])) p++; }
    for (q = p+1; q < s.length() && isalpha(s[q]); q++);
    keys.push_back(s.substr(p, q-p));
    for (p = q; p < s.length() && !isalpha(s[p]); p++);
    if (p == s.length()) return type;
    if (s[p] == 'A') { type = AND; p += 3; }
    else { type = OR; p += 2; }
    while (!isalpha(s[p])) p++;
    for (q = p+1; q < s.length() && isalpha(s[q]); q++);
    keys.push_back(s.substr(p, q-p));
    return type;
}

void debugAns(map<int, set<int> >& ans, const string& info) {
    cout << "DEBUG " << info << " BEGIN\n";
    bool first = true;
    for (auto &b : ans) {
        if (first) first = false;
        else cout << "---------\n";
        for (auto &n : b.second) cout << dat[b.first][n] << "\n";
    }
    cout << "DEBUG " << info << " END\n";
}

int main() {
    int N, M;
    string buf;
    cin >> N; getchar();
    for (int k = 0; k < N; k++) {
        vector<string> lines;
        int i = 0;
        while (getline(cin, buf) && buf[0] != '*') {
            // cout << "DEBUG buf: " << buf << "\n";
            lines.push_back(buf);
            buildIndex(buf, k, i++);
        }
        dat.push_back(lines);
    }
    cin >> M; getchar();
    while (M--) {
        getline(cin, buf);
        // cout << "DEBUG buf: " << buf << "\n";
        vector<string> query;
        int type = parseQuery(buf, query);
        map<int, set<int> > ans;
        // PROCESS A
        for (auto &t : ind[query[0]]) {
            if (!ans.count(t.first)) ans.insert({t.first, set<int>()});
            for (auto &n : t.second) ans[t.first].insert(n);
        }
        // debugAns(ans, string("ans"));
        // PROCESS B
        if (type == AND) {
            map<int, set<int> > tmp;
            set<int> del;
            for (auto &t : ind[query[1]]) {
                if (!ans.count(t.first)) continue;
                if (!tmp.count(t.first)) tmp.insert({t.first, set<int>()});
                for (auto &n : t.second) tmp[t.first].insert(n);
            }
            for (auto &b : ans) {
                if (tmp.count(b.first)) for (auto k : tmp[b.first]) ans[b.first].insert(k);
                else del.insert(b.first);
            }
            for (auto &n : del) ans.erase(n);
        } else if (type == OR) {
            for (auto &t : ind[query[1]]) {
                if (!ans.count(t.first)) ans.insert({t.first, set<int>()});
                for (auto &n : t.second) {
                    ans[t.first].insert(n);
                }
            }
        }
        // debugAns(ans, string("ans"));
        // OUTPUT
        if ((type != NOT && !ans.empty()) || (type == NOT && ans.size() < dat.size())) {
            bool first = true;
            if (type != NOT) {
                for (auto &b : ans) {
                    if (first) first = false;
                    else cout << "----------\n";
                    for (auto &n : b.second) cout << dat[b.first][n] << "\n";
                }
            } else {
                for (int i = 0; i < dat.size(); i++) {
                    if (ans.count(i)) continue;
                    if (first) first = false;
                    else cout << "----------\n";
                    for (auto &s : dat[i]) cout << s << "\n";
                }
            }
        } else cout << "Sorry, I found nothing.\n";
        cout << "==========\n";
    }
    return 0;
}