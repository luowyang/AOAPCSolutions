/**
 * Digit Generator, UVa1583
**/

#include<stdio.h>

#define maxn 100005

int g[maxn] = {0};

int main() {
    for (int n = maxn-1; n >= 0; n--) {
        int sum = n;
        for (int k = n; k > 0; k /= 10)
            sum += k%10;
        if (sum < maxn) g[sum] = n;
    }
    int T, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        printf("%d\n", g[n]);
    }
    return 0;
}