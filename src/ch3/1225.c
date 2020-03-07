/**
 * Digit Count, UVa1225
**/

#include<stdio.h>
#include<string.h>
#define maxn 10005
#define maxm 10

int count[maxn][maxm] = {0};

int main() {
    for (int i = 1; i < maxn; i++) {
        for (int k = i; k > 0; k /= 10)
            count[i][k%10]++;
        memcpy(count[i+1], count[i], sizeof(count[i]));
    }
    int T, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < maxm-1; i++)
            printf("%d ", count[n][i]);
        printf("%d\n", count[n][maxm-1]);    
    }
    return 0;
}