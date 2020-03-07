/**
 * Othello, UVa220
 * 
 * 记录当前玩家，用一个二维数组表示棋盘上的棋子，用两位二进制数编码棋子颜色，用一个二维数组记录合法移动
 * L指令和Q指令可以通过遍历表格实现
 * M指令需要先判断移动是否合法，移动完成后需要检查哪些棋子需要翻转，然后更新合法移动表
 * 
 * 注意事项
 * 1.!a等价于a==0
 * 2.注意行列与下标的对应关系
 * 3.如果没有合法移动，不要忘记改变当前玩家，移动完后再在当前玩家改回去
 * 4.可以用方向向量存储移动方式
 * 5.把棋盘中多余的位置作为哨兵
**/

#include<stdio.h>
#include<string.h>
#define BLACK 2
#define WHITE 1
#define OTHER(i) (i == WHITE ? BLACK : WHITE)
#define maxn 8

int di[8][2] = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};
int board[maxn+2][maxn+2], moves[maxn+2][maxn+2], count[4];
int player;

int readDisk() {
    char ch;
    while ((ch=getchar()) != 'W' && ch != 'B' && ch != '-');
    if (ch == 'W') return WHITE;
    else if (ch == 'B') return BLACK;
    return 0;
}

void flip(int r1, int c1, int r2, int c2, int k) {
    if (board[r1][c1] != board[r2][c2] || !board[r1][c1] || board[r1][c1] != player) return;
    int i, j, dr = di[k][0], dc = di[k][1];
    for (i = r1+dr, j = c1+dc; i != r2 || j != c2; i += dr, j += dc) board[i][j] = player;
}

void check(int r, int c, int flipping) {
    int i, j;
    int other = OTHER(player);
    for (int k = 0; k < 8; k++) {
        int dr = di[k][0], dc = di[k][1];
        for (i = r+dr, j = c+dc; board[i][j] == other; i+=dr, j+=dc);
        if (flipping && board[i][j]) flip(r, c, i, j, k);
        else if (!flipping && !board[i][j] && !(i == r+dr && j == c+dc)) moves[i][j] = 1;
    }
}

void getLegalMoves() {
    memset(moves, 0, sizeof(moves));
    memset(count, 0, sizeof(count));
    for (int i = 1; i <= maxn; i++)
        for (int j = 1; j <= maxn; j++) {
            count[board[i][j]]++;
            if (board[i][j] != player) { continue; }
            check(i, j, 0);
        }
}

void list() {
    int flag = 0, first = 1;
    for (int i = 1; i <= maxn; i++)
        for (int j = 1; j <= maxn; j++)
            if (moves[i][j]) {
                if (first) first = 0;
                else printf(" ");
                printf("(%d,%d)", i, j);
                flag = 1;
            }
    if (flag) printf("\n");
    else printf("No legal move.\n");
}

void show() {
    for (int i = 1; i <= maxn; i++) {
        for (int j = 1; j <= maxn; j++)
            if (!board[i][j]) printf("-");
            else if (board[i][j] == WHITE) printf("W");
            else printf("B");
        printf("\n");
    }
}

void move(int r, int c) {
    if (!moves[r][c]) player = OTHER(player);
    board[r][c] = player;
    check(r, c, 1);
    player = OTHER(player);
    getLegalMoves();
    printf("Black - %2d White - %2d\n", count[BLACK], count[WHITE]);
}

int main() {
    int T, first = 1;
    char cmd[5];
    scanf("%d", &T);
    while (T--) {
        memset(board, 0, sizeof(board));
        for (int i = 1; i <= maxn; i++)
            for (int j = 1; j <= maxn; j++)
                board[i][j] = readDisk();
        player = readDisk();
        getLegalMoves();
        if (!first) printf("\n");
        else first = 0;
        while (scanf("%s", cmd) == 1) {
            if (cmd[0] == 'L') {
                list();
            } else if (cmd[0] == 'Q') {
                show();
                break;
            } else {
                int r = cmd[1] - '0', c = cmd[2] - '0';
                move(r, c);
            }
        }
    }
    return 0;
}