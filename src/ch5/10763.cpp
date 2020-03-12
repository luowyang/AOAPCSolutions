/**
 * Foreign Exchange, UVa10763
**/

#include <map>
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        map<int, map<int, int> > table;
        int a, b;
        while (n--) {
            scanf("%d%d", &a, &b);
            if (!table.count(b) || !(table[b].count(a))) {
                if (!table.count(a)) table.insert({a, map<int, int>()});
                if (!(table[a].count(b))) table[a].insert({b, 0});
                table[a][b]++;
            } else {
                table[b][a]--;
                if (!table[b][a]) table[b].erase(a);
            }
        }
        bool viable = true;
        for (auto &m : table)
            if (m.second.size()) {viable = false; break;}
        if (viable) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}