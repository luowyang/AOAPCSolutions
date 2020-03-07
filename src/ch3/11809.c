/**
 * Floating-Point Numbers, UVa11809
 *
 * 指数最大是2^2^30，直接用double装是不现实的，考虑取对数
 * log10(A)+B=log10(M)+E*log10(2)
 * 接下来暴力搜索就可以了，为了节省点时间可以事先把常量和ln(M)求出来
 * E可以用移位求出，没必要查表
**/

#include<stdio.h>
#include<string.h>
#include<math.h>
#define maxm 10
#define maxn 100
#define eps 1e-5

double m[maxm] = {0.5};

int main() {
    double log2 = log(2);
    double log10 = log(10);
    for (int i = 0; i < maxm; i++)
        m[i] = 1-pow(2, -(i+1));
    for (int i = 0; i < maxm; i++)
        m[i] = log(m[i]);
    char s[maxn], *t;
    while (scanf("%s", s) > 0) {
        if (!strcmp(s, "0e0")) break;
        t = &s[18];
        s[17] = '\0';
        double A;
        sscanf(s, "%lf", &A);
        int B;
        sscanf(t, "%d", &B);
        int lgM = 0, lgE = 1, flag = 1;
        for (int i = 0; i < maxm && flag; i++) {
            for (int j = 1; j <= 30 && flag; j++) {
                int E = (1<<j)-1;
                double delta = abs(log(A)+B*log10-(m[i]+E*log2));
                if (delta < eps) {
                    lgM = i;
                    lgE = j;
                    flag = 0;
                }
            }
        }
        printf("%d %d\n", lgM, lgE);
    }
    return 0;
}