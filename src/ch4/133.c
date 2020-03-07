/**
 * The Dole Queue, UVa133
 * 
 * 这是变种约瑟夫问题，当然可以用环形链表，但是n<20的情况下直接用环形数组更简单
**/

#include<stdio.h>
#include<string.h>
#define maxn 22
#define next(a) (a+1)%maxn
#define prev(b) (b-1+maxn)%maxn

int main() {
    int n, k, m;
    int q[maxn];
    while (scanf("%d%d%d", &n, &k, &m) == 3 && n) {
        int first = 1;
        memset(q, 0, sizeof(q));
        for (int i = 1; i <= n; i++)
            q[i] = 1;
        int a = 0, b = n+1;
        while (n) {
            for (int i = 0; i < k; i++)
                while (!q[a=next(a)]);
            for (int i = 0; i < m; i++)
                while (!q[b=prev(b)]);
            q[a] = q[b] = 0;
            if (!first) printf(",");
            else first = 0;
            if (a != b) {
                printf("%3d%3d", a, b);
                n -= 2;
            } else {
                printf("%3d", a);
                n--;
            }
        }
        printf("\n");
    }
    return 0;
}