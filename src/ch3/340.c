/**
 * Master-Mid Hints, UVa340
**/

#include<stdio.h>

#define maxn 1010

int count[10] = {0};

int main() {
    int n, kase = 0;
    int ans[maxn], guess[maxn];
    while (scanf("%d", &n) > 0 && n) {
        printf("Game %d:\n", ++kase);
        for (int i = 0; i < n; i++) scanf("%d", &ans[i]);
        while (1) {
            for (int i = 0; i < n; i++) scanf("%d", &guess[i]);
            if (!guess[0]) break;
            int A = 0, B = 0;
            int count[10] = {0};
            for (int i = 0; i < n; i++) {
                if (ans[i] == guess[i]) { A++; guess[i] = 0; }
                else count[ans[i]]++;
            }
            for (int i = 0; i < n; i++)
                if ((count[guess[i]]--) > 0) B++;
            printf("    (%d,%d)\n", A, B);
        }
        
    }
    return 0;
}