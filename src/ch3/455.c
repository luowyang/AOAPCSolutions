/**
 * Periodic String, UVa455
**/

#include<stdio.h>
#include<string.h>
#define maxn 85

int equal(char *s, int i, int m) {
    int j = 0;
    while (s[i+j] && s[j] == s[i+j] && ++j < m);
    if (j == m) return 1;
    return 0;
}

int main() {
    int N, first = 1;
    char s[maxn];
    scanf("%d", &N);
    while (N--) {
        scanf("%s", s);
        int m = 0, n = strlen(s);
        while (++m < n) {
            int i = m;
            while (equal(s, i, m) && (i += m) < n);
            if (i == n) break;
        }
        if (first) { printf("%d\n", m); first = !first; }
        else printf("\n%d\n", m);
    }
    return 0;
}