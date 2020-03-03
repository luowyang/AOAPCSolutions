#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    double p = n * 95.0;
    if (n > 3)
        p *= 0.85;
    printf("%.3lf", p);
    return 0;
}