/**
 * Symmetry, UVa1595
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define INFTY 1000000

const int maxN = 1005;
int x[maxN], y[maxN], id[maxN], N;

bool cmp(const int i, const int j) {
    return y[i] < y[j] || (y[i] == y[j] && x[i] < x[j]);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            scanf("%d%d", &x[i], &y[i]);
            id[i] = i;
        }
        sort(id, id+N, cmp);
        int mid = INFTY;
        bool symm = true;
        for (int i = 0, j = 0; i < N && symm; i = j) {
            for (j = i+1; y[id[j]] == y[id[j-1]] && j < N && symm; j++);
            if (mid >= INFTY) mid = x[id[i]] + x[id[j-1]];
            for (int k = 0; k < ((j-i+1)>>1); k++) {
                int t = x[id[i+k]] + x[id[j-1-k]];
                if (t != mid) { symm = false; break; }
            }
        }
        printf("%s\n", symm ? "YES" : "NO");
    }
    return 0;
}