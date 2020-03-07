/**
 * Puzzle, UVa227
**/

#include<stdio.h>

int main() {
    char g[5][5], c;
    int kase = 0, first = 1;
    while ((c = getchar()) != 'Z') {
        if (c == '\n') continue;
        int px = -1, py = -1;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                while (c == '\n' && j < 4) c = getchar();
                if (c == '\n') c = ' ';
                if (c == ' ') { px = i; py = j; }
                g[i][j] = c;
                c = getchar();
            }
        }
        char move;
        int flag = 1;
        while ((move = getchar()) != EOF && move != '0') {
            if (move == 'A') {
                if (px == 0) flag = 0;
                else { g[px][py] = g[px-1][py]; px--; }
            } else if (move == 'B') {
                if (px == 4) flag = 0;
                else { g[px][py] = g[px+1][py]; px++; }
            } else if (move == 'L') {
                if (py == 0) flag = 0;
                else { g[px][py] = g[px][py-1]; py--; }
            } else if (move == 'R') {
                if (py == 4) flag = 0;
                else { g[px][py] = g[px][py+1]; py++; }
            }
        }
        if (first) { printf("Puzzle #%d:\n", ++kase); first = !first; }
        else printf("\nPuzzle #%d:\n", ++kase);
        if (!flag) { printf("This puzzle has no final configuration.\n"); continue; }
        g[px][py] = ' ';
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 4; j++)
                printf("%c ", g[i][j]);
            printf("%c\n", g[i][4]);
        }
    }
    return 0;
}