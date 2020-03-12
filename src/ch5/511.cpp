/**
 * Do You Know The Way to San Jose?, UVa511
**/

#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define eps 1e-6

struct Map {
    string name;
    double x1, y1, x2, y2, a, cx, cy, dr;
    Map(string& n, double a1, double b1, double a2, double b2) {
        name = n;
        x1 = a1 <= a2 ? a1 : a2;
        x2 = a1 <= a2 ? a2 : a1;
        y1 = b1 <= b2 ? b1 : b2;
        y2 = b1 <= b2 ? b2 : b1;
        a = (x2 - x1) * (y2 - y1);
        cx = x1 + x2; cy = y1 + y2;
        dr = abs((y2 - y1)/(x2 - x1)-0.75);
    }
};

map<string, vector<int> > loc;
vector<Map> maps;

double dist(double x1, double y1, double x2, double y2) {
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

bool cmp(double x, double y, int i, int j) {
    double d1 = dist(2*x, 2*y, maps[i].cx, maps[i].cy);     // distance to center
    double d2 = dist(2*x, 2*y, maps[j].cx, maps[j].cy);     // distance to center
    if (d1 < d2) return true; else if (d1 > d2) return false;
    if (maps[i].dr < maps[j].dr) return true; else if (maps[i].dr > maps[j].dr) return false;
    d1 = dist(x, y, maps[i].x2, maps[i].y1);    // distance to right lower conner
    d1 = dist(x, y, maps[j].x2, maps[j].y1);    // distance to right lower conner
    if (d1 < d2) return true; else if (d1 > d2) return false;
    return maps[i].x1 < maps[i].x1;
}

bool contains(double x, double y, int i) {
    return x >= maps[i].x1 && x <= maps[i].x2 && y >= maps[i].y1 && y <= maps[i].y2;
}

int main() {
    string s;
    double x1, y1, x2, y2, x, y;
    cin >> s;
    while (cin >> s && s != "LOCATIONS") {
        cin >> x1 >> y1 >> x2 >> y2;
        maps.push_back(Map(s, x1, y1, x2, y2));
    }
    // for (auto &m: maps) cout << "DEBUG map.name = " << m.name << " area: " << m.a << "\n";
    while (cin >> s && s != "REQUESTS") {
        map<double, int, greater<double> > tmp;
        cin >> x >> y;
        for (unsigned int i = 0; i < maps.size(); i++) {
            if (!contains(x, y, i)) continue;
            if (!tmp.count(maps[i].a)) tmp.insert({maps[i].a, i});
            if (cmp(x, y, i, tmp[maps[i].a])) tmp[maps[i].a] = i;
        }
        vector<int> v;
        for (auto &t : tmp) v.push_back(t.second);
        loc.insert({s, v});
        // cout << "DEBUG loc: " << s << "\n";
        // for (auto &m: v) cout << "DEBUG map.name = " << maps[m].name << "\n";
    }
    int k;
    while (cin >> s && s != "END") {
        cin >> k;
        cout << s << " at detail level " << k << " ";
        if (!loc.count(s)) cout << "unknown location";
        else if (loc[s].empty()) cout << "no map contains that location";
        else {
            bool ill = false;
            if (k > loc[s].size()) { ill = true; k = loc[s].size(); }
            k--;
            if (ill) cout << "no map at that detail level; ";
            cout << "using " << maps[loc[s][k]].name;
        }
        cout << "\n";
    }
    return 0;
}