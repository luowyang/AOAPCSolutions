/**
 * Box, UVa1587
 * 
 * 读入数据时就确保宽在前长在后，方便比较
 * 先按长宽相同两两配对，如果有没法配对的就无法构成长方体
 * 再考虑能否把三对面组合成长方体
**/

#include<stdio.h>

void exch(int a[][2], int i1, int j1, int i2, int j2) {
    int t = a[i1][j1];
    a[i1][j1] = a[i2][j2];
    a[i2][j2] = t;
}

int main() {
    int a[6][2];
    while (1) {
        int k, p = 1;
        for (k = 0; k < 6; k++) {
            if (scanf("%d%d", &a[k][0], &a[k][1]) < 2) break;
            if (a[k][0] > a[k][1]) exch(a, k, 0, k, 1);
        }
        if (k < 6) break;
        for (int i = 0; i < 5; i += 2) {
            for (int j = i+1; j < 6; j++) {
                if (a[i][0] == a[j][0] && a[i][1] == a[j][1]) {
                    exch(a, i+1, 0, j, 0);
                    exch(a, i+1, 1, j, 1);
                }
            }
            if (a[i][0] != a[i+1][0] || a[i][1] != a[i+1][1])
                p = 0;
        }
        k = 2;
        while (k < 5) {
            int c = a[0][0]==a[k][0] ? 0 : 1;
            if (a[0][0] != a[k][c]) { k += 2; continue; }
            int d = a[k][1-c]==a[6-k][0] ? 0 : 1;
            if (a[6-k][d] != a[k][1-c]) { k += 2; continue; }
            if (a[6-k][1-d] != a[0][1]) { k += 2; continue; }
            break;
        }
        if (k >= 5) p = 0;
        printf("%s\n", p ? "POSSIBLE" : "IMPOSSIBLE");
    }
    return 0;
}