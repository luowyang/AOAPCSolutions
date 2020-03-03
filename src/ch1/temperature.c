#include<stdio.h>

int main() {
    double f;
    scanf("%lf", &f);
    double c = (f-32)*5.0/9.0;
    printf("%.3lf", c);
    return 0;
}