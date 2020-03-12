/**
 * The Blocks Problem, UVa101
 * 
 * 用一个vector数组记录每个位置的堆，再用一个数组记录每个块的位置
 * 
 * 注意事项
 * 1.不要写错变量名
**/

#include <vector>
#include <string>
#include <iostream>
using namespace std;

const int maxn = 25;
int n, pos[maxn];
vector<int> pile[maxn];

int find(int p, int a) {
    for (int i = 0; i < pile[p].size(); i++)
        if (pile[p][i] == a) return i;
    return -1;
}

void clearAbove(int p, int h) {
    for (int i = h+1; i < pile[p].size(); i++) {
        int b = pile[p][i];
        pile[b].push_back(b);
        pos[b] = b;
    }
    pile[p].resize(h+1);    // 0-h are retained
}

void pileOnto(int pa, int ha, int pb) {
    for (int i = ha; i < pile[pa].size(); i++) {
        int a = pile[pa][i];
        pile[pb].push_back(a);
        pos[a] = pb;
    }
    pile[pa].resize(ha);     // 0-(ha-1) are retained in pa
}

void print() {
    for (int p = 0; p < n; p++) {
        cout << p << ":";
        for (int a : pile[p]) cout << " " << a;
        cout << endl;
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        pile[i].push_back(i);
        pos[i] = i;
    }
    string s1, s2;
    int a, b;
    while (cin >> s1 >> a >> s2 >> b) {
        if (s1 == "quit") break;
        int pa = pos[a], pb = pos[b];
        if (a == b || pa == pb) continue;
        int ha = find(pa, a), hb = find(pb, b);
        if (s1 == "move") clearAbove(pa, ha);
        if (s2 == "onto") clearAbove(pb, hb);
        pileOnto(pa, ha, pb);
        // cout << "DEBUG: " << s1 << " " << a << " " << s2 << " " << b << endl;
        // print();
    }
    print();
    return 0;
}