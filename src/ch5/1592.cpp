/**
 * Database, UVa1592
 * 
 * 用二维数组保存数据库，然后对列二重枚举，对行扫描，判断列值二元组是否出现过
 * 输入的时候预处理字符串，给每个不同字符串一个编号，把二元组放进map<pair<int,int>, int>中
 * 本题是索引法的又一个例子
 * 注：对行枚举，对列扫描也能过，但是需要的时间比较多
 * 
 * 注意事项
 * 1.如果不是首行，则getline前要用getchar吃掉换行符
 * 2.substr第二个参数是子串长度
 * 3.一对数可以用pair<,>表示
**/

#include <set>
#include <map>
#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 10005, maxm = 12, maxc = 85;
const char lc = ' ', uc = '~';
int db[maxn][maxm];
int n, m, N;
map<string, int> ids;

void readLine(int r) {
    string line, t;
    getline(cin, line); stringstream buf(line);
    int c = 0, id;
    while (getline(buf, t, ',')) {
        map<string, int>::iterator it = ids.find(t);
        if (it == ids.end()) ids.insert({t, (id = N++)});
        else id = it->second;
        db[r][c++] = id;
    }
}

int main() {
    while (cin >> n >> m) {
        N = 0; ids.clear(); getchar();
        for (int i = 0; i < n; i++) readLine(i);
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < m; j++)
        //         printf("%d|", db[i][j]);
        //     printf("\n");
        // }
        int r1, r2 = 0, c1, c2, isPNF = 1;
        for (int i = 0; i < m && isPNF; i++) {
            for (int j = i+1; j < m && isPNF; j++) {
                map<pair<int,int>, int> tup;
                r1 = r2 = 0;
                for (int r = 0; r < n; r++) {
                    map<pair<int,int>, int>::iterator it = tup.find({db[r][i], db[r][j]});
                    if (it == tup.end()) tup.insert({{db[r][i], db[r][j]}, r+1});
                    else {
                        r1 = it->second; r2 = r + 1;
                        c1 = i + 1; c2 = j + 1;
                        isPNF = 0; break;
                    }
                }
            }
        }
        if (isPNF) printf("YES\n");
        else printf("NO\n%d %d\n%d %d\n", r1, r2, c1, c2);
    }
    return 0;
}