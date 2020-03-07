/**
 * Crossword Answers, UVa232
**/

#include<stdio.h>
#include<string.h>

int isStart(char a[][12], int i, int j) {
    if (i <= 0 || j <= 0 || a[i-1][j] == '*' || a[i][j-1] == '*')
        return a[i][j] == '*' ? 0 : 1;
    return 0;
}

int main() {
    int r, c;
    char a[12][12], ch;
    int w[12*12], count, first = 1, kase = 0;
    while (scanf("%d", &r) > 0 && r != 0) {
        scanf("%d", &c);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                while ((ch = getchar()) == '\n' || ch == ' ');
                a[i][j] = ch;
            }
        }
        memset(w, 0, sizeof(w));
        count = 0;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                if (isStart(a, i, j)) w[++count] = i*12+j;
        if (first) { printf("puzzle #%d:\n", ++kase); first = !first; }
        else printf("\npuzzle #%d:\n", ++kase);
        printf("Across\n");
        for (int n = 1; n <= count; n++) {
            int i = w[n]/12, j = w[n]%12;
            if (j <= 0 || a[i][j-1] == '*') {
                printf("%3d.", n);
                while (j < c && a[i][j] != '*')
                    printf("%c", a[i][j++]);
                printf("\n");
            }
        }
        printf("Down\n");
        for (int n = 1; n <= count; n++) {
            int i = w[n]/12, j = w[n]%12;
            if (i <= 0 || a[i-1][j] == '*') {
                printf("%3d.", n);
                while (i < r && a[i][j] != '*')
                    printf("%c", a[i++][j]);
                printf("\n");
            }
        }
    }
    return 0;
}