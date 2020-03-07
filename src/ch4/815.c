/**
 * Flooded, UVa815
 * 
 * 先对海拔排序，然后从海拔最低的格点开始，统计每个海拔最多能容纳多少水，当容积第一次大于水的总体积时求水面高度
 * 公式V=A*sum(hw-hi)=A*(hw*k-sum(hi))
 * 
 * 注意事项
 * 1.注意有可能所有格子都被淹没
 * 2.小心计算精度
**/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxm 30
#define A 100
#define eps 1e-5

int cmp(const void *i, const void *j) {
    return *(int *)i - *(int *)j;
}

int main() {
    int h[maxm*maxm];
    int m, n, V, kase = 0;
    while (scanf("%d%d", &m, &n) == 2 && m) {
        for (int i = 0; i < m*n; i++)
            scanf("%d", &h[i]);
        scanf("%d", &V);
        qsort(h, m*n, sizeof(int), cmp);
        int hi, hs, k;
        hs = k = 0; hi = h[k];
        while ((hi*k-hs)*A < V && k < m*n) {
            while (h[k] == hi) {hs += hi; k++; }
            hi = h[k];
        }
        double hw = ((double)V/A + hs)/k;
        double per = k*100.0/((m*n)+eps);
        printf("Region %d\nWater level is %.2lf meters.\n%.2lf percent of the region is under water.\n\n", ++kase, hw, per);
    }
    return 0;
}