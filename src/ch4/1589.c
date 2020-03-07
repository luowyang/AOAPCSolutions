/**
 * Xiangqi, UVa1589
 * 
 * 用一个数组记录棋盘上的棋子，用结构体数组记录红方棋子
 * 对于黑将所有可能的行动，遍历红方所有棋子，检查能否威胁到黑将
 * 注意事项：
 * 1.%c会读入换行符
 * 3.黑将如果直接面对红将则黑方胜
 * 4.黑将移动后有可能吃掉一个棋子，吃掉的棋子需要在移回原位时复原
**/

#include<stdio.h>
#include<string.h>
#define maxd 10
#define maxr 11
#define maxc 10

struct {
    char type;
    int r, c;
} reds[maxd];
int board[maxr][maxc];
int N, gr, gc, isCheckmate;

int hasPiece(int r, int c) {
    if (r < 1 || r > 10) return 1;
    if (c < 1 || r > 9) return 1;
    return board[r][c] != 0;
}

void inspect(int r0, int c0) {
    int removed = board[r0][c0];
    board[r0][c0] = -1;
    int flag = 0;
    for (int k = 1; k <= N; k++) {
        if (k == removed) continue;
        char type = reds[k].type;
        int r = reds[k].r, c = reds[k].c;
        int i, j;
        if (type == 'R' || type == 'C') {
            i = r;
            if (type == 'C') for (i--; i >= 1 && !hasPiece(i, c); i--);
            for (i--; i >= 1 && !hasPiece(i, c); i--);
            if (i == r0 && c == c0) { flag = 1; break; }
            i = r;
            if (type == 'C') for (i++; i <= 3 && !hasPiece(i, c); i++);
            for (i++; i <= 3 && !hasPiece(i, c); i++);
            if (i == r0 && c == c0) { flag = 1; break; }
            j = c;
            if (type == 'C') for (j--; j >= 4 && !hasPiece(r, j); j--);
            for (j--; j >= 4 && !hasPiece(r, j); j--);
            if (r == r0 && j == c0) { flag = 1; break; }
            j = c;
            if (type == 'C') for (j++; j <= 6 && !hasPiece(r, j); j++);
            for (j++; j <= 6 && !hasPiece(r, j); j++);
            if (r == r0 && j == c0) { flag = 1; break; }
        } else if (type == 'H') {
            if (!hasPiece(r-1, c) && ((r-2 == r0 && c-1 == c0) || (r-2 == r0 && c+1 == c0))) { flag = 1; break; }
            if (!hasPiece(r+1, c) && ((r+2 == r0 && c-1 == c0) || (r+2 == r0 && c+1 == c0))) { flag = 1; break; }
            if (!hasPiece(r, c-1) && ((r-1 == r0 && c-2 == c0) || (r+1 == r0 && c-2 == c0))) { flag = 1; break; }
            if (!hasPiece(r, c+1) && ((r-1 == r0 && c+2 == c0) || (r+1 == r0 && c+2 == c0))) { flag = 1; break; }
        } else {
            for (i = r-1; i >= 1 && !hasPiece(i, c); i--);
            if (i == r0 && c == c0) { flag = 1; break; }
        }
    }
    if (!flag) isCheckmate = 0;
    board[r0][c0] = removed;
}

int main() {
    char ch;
    while (scanf("%d%d%d", &N, &gr, &gc) == 3 && N) {
        memset(board, 0, sizeof(board));
        for (int i = 1; i <= N; i++) {
            while ((ch = getchar()) != 'G' && ch != 'R' && ch != 'H' && ch != 'C');
            reds[i].type = ch;
            scanf("%d%d", &reds[i].r, &reds[i].c);
            board[reds[i].r][reds[i].c] = i;
        }
        isCheckmate = 1;
        if (gr > 1) inspect(gr-1, gc);
        if (gr < 3) inspect(gr+1, gc);
        if (gc > 4) inspect(gr, gc-1);
        if (gc < 6) inspect(gr, gc+1);
        int i;
        for (i = gr; i <= maxr && !hasPiece(i, gc); i++);
        if (hasPiece(i, gc) && reds[board[i][gc]].type == 'G') isCheckmate = 0;
        if (isCheckmate) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}