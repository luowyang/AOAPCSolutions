/**
 * Ancient Cipher, UVa1339
 * 
 * 先用数组统计字符出现次数，对计数结果排序后比较
 * 当且仅当排序后计数数组相同时能够建立一一映射，证明略
**/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxn 105
#define maxm 26

int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int sc[maxm], tc[maxm];
    char s[maxn], t[maxn];
    while (scanf("%s%s", s, t) == 2) {
        memset(sc, 0, sizeof(sc));
        memset(tc, 0, sizeof(tc));
        for (int i = 0; s[i]; i++)
            sc[s[i]-'A']++;
        for (int i = 0; t[i]; i++)
            tc[t[i]-'A']++;
        qsort(sc, maxm, sizeof(int), cmp);
        qsort(tc, maxm, sizeof(int), cmp);
        int flag = 1;
        for (int i = 0; i < maxm && flag; i++)
            if (sc[i] != tc[i]) flag = 0;
        printf("%s\n", flag?"YES":"NO");
    }
    return 0;
}