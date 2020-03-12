/**
 * 产生100个[0,n]区间内近似均匀分布的整数
 * 警告：不适合高精度应用
**/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

int main() {
    srand(time(NULL));
    double ti = time(NULL) /CLOCKS_PER_SEC;
    double t;
    const int n = 100;
    int r, count[n+1];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < 100; i++) {
        t = (double)rand() / RAND_MAX;
        r = t * n;
        count[r]++;
        printf("%d ", r);
    }
    printf("\n");
    for (int i = 0; i < n+1; i++)
        printf("count[%d] = %d\n", i, count[i]);
    cout << ti - (double)time(NULL) /CLOCKS_PER_SEC << "\n";
}