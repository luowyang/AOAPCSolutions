/**
 * Ducci Sequence, UVa1594
**/

#include <unordered_set>
#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

bool nonZero(vector<int>& t) {
    for (unsigned int i = 0; i < t.size(); i++)
        if (t[i]) return true;
    return false;
}

vector<int> ducci(const vector<int>& t) {
    vector<int> s;
    for (unsigned int i = 0; i < t.size()-1; i++) s.push_back(abs(t[i]-t[i+1]));
    s.push_back(abs(t[0]-t[t.size()-1]));
    return s;
}

void printTup(vector<int>& t) {
    for (unsigned int i = 0; i < t.size(); i++) cout << t[i] << " ";
    cout << "\n";
}

struct vecHash {
    static size_t const p = 16769023;
    static size_t const k = 1000;
    size_t operator()(const vector<int>& v) const {
        size_t h = 0;
        for (unsigned int i = 0; i < v.size(); i++)
            h = (h * k + hash<int>()(v[i])) % p;
        return h;
    }
};

int main() {
    int T, n;
    cin >> T;
    while (T--) {
        unordered_set<vector<int>, vecHash> tups;
        vector<int> t;
        int k;
        cin >> n;
        while (n--) {
            cin >> k;
            t.push_back(k);
        }
        printTup(t);
        bool isLoop = false;
        while (nonZero(t)) {
            if (tups.count(t)) { isLoop = true; break; }
            tups.insert(t);
            t = ducci(t);
            printTup(t);
        }
        printf("%s\n", isLoop ? "LOOP" : "ZERO");
        // if (isLoop) printTup(t);
    }
    return 0;
}