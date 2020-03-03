#include<stdio.h>
#include<math.h>

#define PI 3.14159265358979

int main() {
    int n;
    scanf("%d", &n);
    double theta = n / 180.0 * PI;
    printf("%.3lf\n%.3lf\n", sin(theta), cos(theta));
    return 0;
}