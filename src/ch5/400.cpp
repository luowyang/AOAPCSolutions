/**
 * Unix ls, UVa400
 * 
 * 先求出最长文件名并在对文件名排序，然后算出每列的文件名数量
 * 公式为：kM+2*(k-1)<=60，k尽量大，因此k=(A+2)/(M+2)，向下取整行数r=(N-1)/k + 1
 * 
 * 注意事项
 * 1.一般来说卡顿一会然后退出是因为发生了段错误，检查是否有非法内存访问，比如是否写错了变量名
 * 2.注意是行主序输出，外循环变量取为行数，内循环变量取为待输出文件名序号
 * 3.每一行的最后一列都只补齐到M列
**/

#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxc = 60, maxn = 102;
string names[maxn];
int N, M, k, r;

void printName(int k, int len) {
    cout << names[k];
    for (int i = names[k].length(); i < len; i++)
        printf(" ");
}

int main() {
    while (cin >> N) {
        M = 0;
        for (int i = 0; i < N; i++) {
            cin >> names[i];
            if (names[i].length() > M) M = names[i].length();
        }
        k = (maxc + 2) / (M + 2); r = (N - 1) / k + 1;
        // printf("DEBUG M: %d\nDEBUG k: %d\nDEBUG r: %d\n", M, k, r);
        sort(names, names + N);
        // for (int i = 0; i < N; i++) cout << names[i] << "\n";
        for (int i = 0; i < maxc; i++) printf("-");
        printf("\n");
        for (int i = 0; i < r; i++) {
            int j;
            for (j = i; (j-i) < (k-1)*r && j + r < N; j += r) printName(j, M+2);
            if (j < N) printName(j, M);
            printf("\n");
        }
    }
    return 0;
}