/**
 * DNA Consensus String, UVa1368
**/

#include<stdio.h>
#include<string.h>
#define maxn 1005
#define maxm 55

char s[maxm][maxn];
char dna[maxn];

int main() {
    int T;
    int count[26] = {0};
    scanf("%d", &T);
    while (T--) {
        int m = 0, n = 0, dist = 0;
        scanf("%d%d", &m, &n);
        for (int i = 0; i < m; i++)
            scanf("%s", s[i]);
        for (int j = 0; j < n; j++) {
            memset(count, 0, sizeof(count));
            for (int i = 0; i < m; i++)
                count[s[i][j]-'A']++;
            int max = 0;
            for (int k = 1; k < 26; k++)
                if (count[k] > count[max]) max = k;
            dna[j] = max + 'A';
            dist += (m - count[max]);
        }
        dna[n] = '\0';
        printf("%s\n%d\n", dna, dist);
    }
    return 0;
}