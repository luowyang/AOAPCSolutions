#include<stdio.h>

int main() {
    int a, b, c, kase = 0;
    while (scanf("%d%d%d", &a, &b, &c) > 0) {
        int n = a;
        while (n < 10) n += 3;
        for (; n <= 100; n+=3) {
            if (n % 5 != b || n % 7 != c) continue;
            printf("Case %d: %d\n", ++kase, n);
            break;
        }
        if (n > 100) printf("Case %d: No answer\n", ++kase);
    }
    return 0;
}