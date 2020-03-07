/**
 * Repeating Decimals, UVa202
**/

#include<stdio.h>
#include<string.h>
#define maxn 3005

char s[maxn];
char cycle[maxn];

int main() {
    int a, b, c, n, m;
    
    while (scanf("%d%d", &a, &b) > 1) {
        int begin, end = 0;
        n = a; m = b;
        memset(cycle, -1, sizeof(cycle));
        a %= b;
        while (a && cycle[a] < 0) {
            cycle[a] = end;
            a *= 10; c = a/b; a %= b;
            s[end++] = c + '0';
        }
        begin = cycle[a];
        s[begin+50] = s[begin+51] = s[begin+52] = '.';
        s[begin+53] = '\0';
        if (end-begin <= 50) s[end] = '\0';
        printf("%d/%d = %d.", n, m, n/m);
        if (!a) { printf("%s(0)\n", s); begin = 0; end = 1; }
        else {
            for (int i = 0; i < begin; i++)
                printf("%c", s[i]);
            printf("(%s)\n", &s[begin]);
        }
        printf("   %d = number of digits in repeating cycle\n\n", end-begin);
    }
    return 0;
}