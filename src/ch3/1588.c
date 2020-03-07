/**
 * Kickdown, UVa1588
 *
 * 记录driven的最左端的位置，暴力搜索
 * 为了减轻边界检查的负担需要把数组开大一点，把左右的空位当做哨兵
**/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxm 105
#define maxn 305

int p[maxn];

int len(int mlen, int dlen, int i) {
    if (i < dlen) return mlen+dlen-i;
    else if (i < mlen) return mlen;
    else return i;
}

int main() {
    char *master, *driven;
    int d[maxm];
    master = (char*)malloc(sizeof(char)*maxm);
    driven = (char*)malloc(sizeof(char)*maxm);
    while (scanf("%s%s", master, driven) > 1) {
        memset(p, 0, sizeof(p));
        if (strlen(master) < strlen(driven)) {
            char* t = master;
            master = driven;
            driven = t;
        }
        int mlen, dlen;
        mlen = strlen(master);
        dlen = strlen(driven);
        for (int i = 0; i < mlen; i++)
            p[i+dlen] = master[i] - '0';
        for (int i = 0; i < dlen; i++)
            d[i] = driven[i] - '0';
        int min = mlen+dlen;
        for (int i = 0; i < min; i++) {
            int j;
            for (j = 0; j < dlen && d[j]+p[i+j] <= 3; j++);
            if (j == dlen && len(mlen, dlen, i) < min) min = len(mlen, dlen, i);
        }
        printf("%d\n", min);
    }
    return 0;
}