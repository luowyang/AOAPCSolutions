/**
 * Spreadsheet Tracking, UVa512
 * 
 * 用结构体数组保存操作序列，遇到查询时模拟操作
 * 注意事项
 * 1.注意输出格式！
**/

#include<stdio.h>
#include<string.h>
#define maxd 10000

struct {
    char op[5];
    int A;
    int pos[20];
} cmd[maxd];
int R, C, ops;

int simulate(int* r, int* c) {
    for (int i = 0; i < ops; i++) {
        if (cmd[i].op[0] == 'E') {
            if (cmd[i].pos[0] == *r && cmd[i].pos[1] == *c) {
                *r = cmd[i].pos[2];
                *c = cmd[i].pos[3];
            } else if (cmd[i].pos[2] == *r && cmd[i].pos[3] == *c) {
                *r = cmd[i].pos[0];
                *c = cmd[i].pos[1];
            }
        } else {
            int* p = (cmd[i].op[1] == 'R' ? r : c);
            int n = 0;
            if (cmd[i].op[0] == 'I') {
                for (int j = 0; j < cmd[i].A; j++)
                    if (cmd[i].pos[j] <= *p) n++;
            } else {
                for (int j = 0; j < cmd[i].A; j++)
                    if (cmd[i].pos[j] < *p) n--;
                    else if (cmd[i].pos[j] == *p) return 0;
            }
            *p += n;
        }
        //printf("DEBUG: r=%d, c=%d\n", *r, *c);
        //printf(" ");
    }
    return 1;
}

int main() {
    int kase = 0, first = 1;
    while (scanf("%d%d%d", &R, &C, &ops) == 3 && R) {
        for (int i = 0; i < ops; i++) {
            scanf("%s", cmd[i].op);
            if (cmd[i].op[0] == 'E') {
                cmd[i].A = 4;
                scanf("%d%d%d%d", &cmd[i].pos[0], &cmd[i].pos[1], &cmd[i].pos[2], &cmd[i].pos[3]);
            } else {
                scanf("%d", &cmd[i].A);
                for (int j = 0; j < cmd[i].A; j++)
                    scanf("%d", &cmd[i].pos[j]);
            }
        }
        if (!first) printf("\n");
        else first = 0;
        int qs, r, c;
        scanf("%d", &qs);
        printf("Spreadsheet #%d\n", ++kase);
        while (qs--) {
            scanf("%d%d", &r, &c);
            printf("Cell data in (%d,%d) ", r, c);
            if (!simulate(&r, &c)) printf("GONE\n");
            else printf("moved to (%d,%d)\n", r, c);
        }
    }
    return 0;
}