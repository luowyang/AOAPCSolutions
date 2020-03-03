#include<stdio.h>

int main() {
    unsigned long long k = 0x0010000000000000;
    double* d = (double*)&k;
    printf("%e\n", *d);
    printf("%u\n", 0&&!1);
    return 0;
}