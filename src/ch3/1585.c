/**
 * Score, UVa1585
**/

#include<stdio.h>
#define maxn 85

int main() {
    int T;
    char s[maxn];
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        int score = 0, count = 0;
        for (int i = 0; s[i]; i++) {
            if (s[i] == 'O') score += ++count;
            else count = 0;
        }
        printf("%d\n", score);
    }
    return 0;
}