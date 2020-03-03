#include<stdio.h>

int main() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    if (a <= 0 || b <= 0 || c <= 0 || a+b <= c || a+c <= b || b+c <= a)
        printf("not a triangle\n");
    else {
        int t;
        if (a > b) { t = a; a = b; b = t; }
        if (b > c) { t = b; b = c; c = t; }
        if (a*a + b*b == c*c)
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}