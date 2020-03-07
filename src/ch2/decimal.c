#include<stdio.h>

int main() {
    int a, b, c, kase = 0;
    while (scanf("%d%d%d", &a, &b, &c) == 3 && a && b && c) {
        printf("%d.", a/b);
        a = (a % b) * 10;
        for (int i = 1; i < c; i++) {
            printf("%d", a/b);
            a = (a % b) * 10;
        }
        int r = a/b;
        a = (a % b) * 10;
        if (a/b >= 5) r++;
        printf("%d", r);
        printf("\n");
    }
    return 0;
}