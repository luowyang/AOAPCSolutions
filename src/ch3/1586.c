/**
 * Molar Mass, UVa1585
**/

#include<stdio.h>
#include<ctype.h>
#define maxn 85
#define maxm 30
#define massC 12.01
#define massH 1.008
#define massO 16.00
#define massN 14.01

int main() {
    int T;
    char s[maxn];
    scanf("%d", &T);
    while (T--) {
        int count[maxm] = {0};
        scanf("%s", s);
        int j;
        for (int i = 0; s[i]; i = j) {
            j = i+1;
            int n = 0;
            for (; isdigit(s[j]); j++) {
                n = n*10+s[j]-'0';
            }
            count[s[i]-'A'] += n;
            if (j == i+1) count[s[i]-'A']++;
        }
        double mass = 0.0;
        mass += count['C'-'A']*massC;
        mass += count['H'-'A']*massH;
        mass += count['O'-'A']*massO;
        mass += count['N'-'A']*massN;
        printf("%.3lf\n", mass);
    }
    return 0;
}