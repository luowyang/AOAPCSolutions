/**
 * RAID!, UVa509
 * 
 * 用一个二维数组保存数据块，用异或实现奇偶校验，注意异或的性质
 * 
 * 注意事项
 * 1.以下情况下磁盘无效：一组校验码中有两位及以上缺失；没有缺失的情况下奇偶校验失败
**/

#include<stdio.h>
#include<string.h>
#define maxd 10
#define maxs 100
#define maxb 105

char raid[maxb][maxd][maxs];
int pty, d, s, b;

void readData() {
    char ch, *p;
    for (int j = 0; j < d; j++) {
        while ((ch=getchar()) != '0' && ch != '1' && ch != 'x');
        for (int i = 0; i < b; i++) {
            p = raid[i][j];
            for (int k = 0; k < s; k++) {
                p[k] = ch;
                ch = getchar();
            }
            p[s] = '\0';
        }
    }
}

unsigned int hex(char *p) {
    return ((p[0]-'0')<<3) + ((p[1]-'0')<<2) + ((p[2]-'0')<<1) + (p[3]-'0');
}

void printData() {
    char data[maxs*maxd], *p = data;
    for (int i = 0; i < b; i++) {
        for (int j = 0; j < d; j++) {
            if (j == i % d) continue;
            strcpy(p, raid[i][j]);
            while (p[0]) p++;
        }
        int len = strlen(data);
        for (p = data; p-data+4 <= len; p += 4) printf("%X", hex(p));
        strcpy(data, p);
        for (p = data; p[0]; p++);
    }
    // printf("(DEBUG: %c)", data[0]);
    if (data[0]) {
        for (; p-data < 4; p++) p[0] = '0';
        printf("%X", hex(data));
    }
}

int main() {
    char ch[5];
    int kase = 0;
    while (scanf("%d%d%d%s", &d, &s, &b, ch) == 4 && d) {
        pty = ch[0] == 'E' ? 0 : 1;
        readData();
        printf("Disk set %d is ", ++kase);
        int valid = 1;
        for (int i = 0; i < b && valid; i++) {
            for (int k = 0; k < s && valid; k++) {
                int unav = -1, p = 0;
                for (int j = 0; j < d; j++) {
                    char ch = raid[i][j][k];
                    if (ch == 'x') {
                        if (unav < 0) unav = j;
                        else { valid = 0; break; }
                    } else {
                        p ^= (ch - '0');
                    }
                }
                if (unav < 0 && p != pty) valid = 0;
                if (valid && unav >= 0) raid[i][unav][k] = (p^pty) + '0';
            }
        }
        if (valid) {
            printf("valid, contents are: ");
            printData(); printf("\n");
        } else {
            printf("invalid.\n");
        }
    }
    return 0;
}