/**
 * Exchange, UVa1598
**/

#include <set>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define BUY 0
#define SELL 1
#define maxn 10005

struct tran {
    int type;
    bool act;
    int sz, pr;
};

tran t[maxn];

struct cmp {
    bool operator() (int i, int j) const {
        if (t[i].type == BUY)
            return t[i].pr > t[j].pr || (t[i].pr == t[j].pr && i < j);
        else
            return t[i].pr < t[j].pr || (t[i].pr == t[j].pr && i < j);
    }
};

int main() {
    int n;
    bool first = true;
    while (cin >> n) {
        set<int, cmp> q[2];      // guaranteed to have no inactive order
        char s[10];
        if (first) first = false;
        else printf("\n");
        for (int i = 1; i <= n; i++) {
            scanf("%s", s);
            t[i].act = true;
            if (s[0] == 'C') {
                int k;
                scanf("%d", &k); 
                if (t[k].act) {
                    t[k].act = false;
                    q[t[k].type].erase(k);
                }
            } else {
                scanf("%d%d", &t[i].sz, &t[i].pr);
                int m, p, th, ot;
                th = s[0] == 'B' ? BUY : SELL; ot = 1 - th;
                t[i].type = th;
                for (int f = *q[ot].begin(); !q[ot].empty() && t[i].sz; f = *q[ot].begin()) {
                    if ((th == BUY && t[f].pr > t[i].pr) || (th == SELL && t[f].pr < t[i].pr)) break;
                    m = min(t[f].sz, t[i].sz);
                    p = t[f].pr;
                    t[f].sz -= m;
                    if (!t[f].sz) { t[f].act = false; q[ot].erase(f); }
                    t[i].sz -= m;
                    if (!t[i].sz) t[i].act = false;
                    printf("TRADE %d %d\n", m, p);
                }
                if (t[i].sz) q[th].insert(i);
            }
            // quote
            int s[2], p[2];
            s[0] = p[0] = s[1] = 0; p[1] = 99999;
            for (int i = 0; i < 2; i++) {
                if (!q[i].empty()) {
                    p[i] = t[*q[i].begin()].pr;
                    for (auto &b : q[i])
                        if (t[b].pr == p[i]) s[i] += t[b].sz;
                        else break;
                }
            }
            printf("QUOTE %d %d - %d %d\n", s[0], p[0], s[1], p[1]);
        }
    }
    return 0;
}