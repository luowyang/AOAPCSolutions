/**
 * Team Queue, UVa540
 * 
 * 用queue表示外队列，内队列用queue数组表示，用map记录每个人属于哪个内队列
 * 
 * 注意事项
 * 1.尽可能用scanf代替流操作，加快速度
 * 2.如果要用vector装队列，则赋值前一定要先调用resize()来避免非法内存访问
**/

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

#define maxn 10
#define maxt 1005

int main() {
    int t, k, m, id, kase = 0;
    char op[maxn];
    while (cin >> t && t) {
        map<int, int> team;
        for (int i = 0; i < t; i++) {
            scanf("%d", &k);
            while (k--) {
                scanf("%d", &m);
                team[m] = i;
            }
        }
        printf("Scenario #%d\n", ++kase);
        queue<int> q, groups[maxt];
        while (scanf("%s", op) == 1 && op[0] != 'S') {
            if (op[0] == 'E') {
                scanf("%d", &m);
                id = team[m];
                if (groups[id].empty()) q.push(id);
                groups[id].push(m);
            } else {
                id = q.front();
                printf("%d\n", groups[id].front());
                groups[id].pop();
                if (groups[id].empty()) q.pop();
            }
        }
        printf("\n");
    }
    return 0;
}