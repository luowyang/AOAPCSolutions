/**
 * Squares, UVa201
 * 
 * 第一种算法是先预处理：自右向左扫描所有行再自右向左扫描所有列，根据连续边数记录每个点的搜索上界，然后再搜索
 * 第二种算法是预处理时分别记录最大向右和向下连续边，搜索上界就是较小者，搜索的时候利用连续边信息剪枝
 * 上面两种算法的渐进复杂度上界都是立方级别的
 * 本题规模较小，因此直接暴力搜索即可，复杂度上界是四次方级别的
 * 
 * 用两位二进制数编码每个顶点的向右和向下是否有边，用二维数组记录点阵信息
 * 依次对每个顶点遍历搜索所有可能的正方形边长，可以根据顶点坐标和向右向下最大连续边数确定搜索上界
 * 注意事项
 * 1.忽略非法输入，用按位或避免重复添加边
**/

#include<stdio.h>
#include<string.h>
#define maxn 12
#define hasRight(k) (k&1)
#define hasDown(k) (k&2)

int n, count[maxn], mat[maxn][maxn];

void stat(int r, int c) {
    int m = n-r;
    for (int i = 1; i <= m; i++) {
        if (!hasRight(mat[r][c+i-1]) || !hasDown(mat[r+i-1][c])) break;
        int hasRect = 1;
        for (int j = 0; j < i; j++) {
            if (!hasDown(mat[r+j][c+i]) || !hasRight(mat[r+i][c+j])) {
                hasRect = 0;
                break;
            }
        }
        if (hasRect) count[i]++;
    }
}

void printMat() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) printf("%3d", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    int m, kase = 0, first = 1;
    while (scanf("%d%d", &n, &m) == 2) {
        memset(mat, 0, sizeof(mat));
        char ch;
        int k1, k2;
        for (int i = 0; i < m; i++) {
            while ((ch=getchar()) != 'H' && ch != 'V');
            scanf("%d%d", &k1, &k2);
            if (k2 >= n) continue;
            if (ch == 'H') mat[k1][k2] |= 1;
            else mat[k2][k1] |= 2;
            //printMat();
        }
        memset(count, 0, sizeof(count));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                stat(i, j);
        if (!first) printf("\n**********************************\n\n");
        else first = 0;
        printf("Problem #%d\n\n", ++kase);
        int tot = 0;
        for (int i = 1; i <= n; i++) {
            if (count[i]) printf("%d square (s) of size %d\n", count[i], i);
            tot += count[i];
        }
        if (!tot) printf("No completed squares can be found.\n");
    }
    return 0;
}