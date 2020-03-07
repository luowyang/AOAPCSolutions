/**
 * Circular Sequence, UVa1584
**/

#include<stdio.h>
#include<string.h>

int less(const char* s, int n, int i, int j) {
    for (int k = 0; k < n; k++) {
        if      (s[i] < s[j]) return 1;
        else if (s[i] > s[j]) return 0;
        if (++i == n) i = 0;
        if (++j == n) j = 0;
    }
    return 0;
}

int main() {
    int T;
    char s[105];
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        int min = 0;
        int n = strlen(s);
        for (int i = 1; i < n; i++)
            if (less(s, n, i, min)) min = i;
        for (int i = 0; i < n; i++) {
            putchar(s[min++]);
            if (min == n) min = 0;
        }
        printf("\n");
    }
    return 0;
}