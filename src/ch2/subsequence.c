#include<stdio.h>

int main() {
    int n, m, kase = 0;
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        double sum = 0.0;
        for (int i = n; i <= m; i++)
            sum += 1.0/i/i;
        printf("Case %d: %.5lf\n", ++kase, sum);
    }
    return 0;
}