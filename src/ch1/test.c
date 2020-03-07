#include<stdio.h>
#include<time.h>

int main() {
    const int mod = 1000000;
    int n;
    int sum = 0.0;
    int fact = 1;
    scanf("%d", &n);
    long long t = clock();
    for (int i = 1; i <= n; i++) {
        fact = (fact * i) % mod;
        sum = (fact + sum) % mod;
    }
    printf("%06d\n", sum);
    printf("time consumed: %.2f\n", (double)(clock() - t) / CLOCKS_PER_SEC);
    return 0;
}