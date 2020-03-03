#include<stdio.h>

int main() {
    int i, j, k;
    scanf("%d%d%d", &i, &j, &k);
    double avg = (double)(i+j+k) / 3.0;
    printf("%.3lf\n", avg);
    return 0;
}