/**
 * The SetStack Computer, UVa12096
 * 
 * 为每个不同的集合分配一个唯一的ID， 每个集合都是ID的集合，栈则是ID的栈
 * 用set<int>实现集合，使得ID有序方便比较，同时能去重，用一个vector记录每个ID对应的集合，用map记录集合的ID
 * 
 * 注意事项
 * 1.改变集合元素时不要直接操作原集合的指针，而是要构造新集合
 * 2.不同的指令可以合并重合的操作
 * 3.双向索引法
**/

#include <set>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

#define ALL(x) x.begin(),x.end()
#define INS(x) inserter(x,x.begin())

const int maxn = 2020;
vector<set<int>> sets;
map<set<int>, int> ids;

int getID(set<int> s) {
    if (ids.count(s)) return ids[s];
    sets.push_back(s);
    return ids[s] = sets.size() - 1;
}

int main() {
    int T, N;
    string op;
    cin >> T;
    while (T--) {
        stack<int> cpt;
        cin >> N;
        while (N--) {
            cin >> op;
            if (op[0] == 'P') cpt.push(getID(set<int>()));
            else if (op[0] == 'D') cpt.push(cpt.top());
            else {
                set<int> a = sets[cpt.top()]; cpt.pop();
                set<int> b = sets[cpt.top()]; cpt.pop();
                set<int> x;
                //if (op[0] == 'U') set_union(ALL(a), ALL(b), INS(x));
                //else if (op[0] == 'I') set_intersection(ALL(a), ALL(b), INS(x));
                //else {x = b; x.insert(getID(a));}
                cpt.push(getID(x));
            }
            cout << sets[cpt.top()].size() << endl;
        }
        cout << "***" << endl;
    }
    return 0;
}