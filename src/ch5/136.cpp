/**
 * Ugly Numbers, UVa136
 * 
 * 用ugly[i]表示第i个丑数，ugly[0]=1，则ugly[i]一定是由ugly[k]乘{2,3,5}得到的，其中0<=k<i
 * 类似DP的思想，ugly[i]=min(ugly[k]*{2,3,5}), for all 0<=k<i
 * “状态”更新过程：初始化ugly[0]=1，求出所有ugly[k]*{2,3,5}，则ugly[k+1]必然是候选集合中最小的
 * 
 * 注意事项
 * 1.注意本题的思路和DP很像
 * 2.int会溢出，因此采用long long
 * 3.set的第一个元素就是最小元素，取出它后记得删掉它
**/

#include <set>
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long LL;
LL factor[3] = {2, 3, 5};

int main() {
    set<LL> s;
    s.insert(1);
    for (int i = 1; i < 1500; i++) {
        LL num = *s.begin();
        s.erase(s.begin());
        for (int j = 0; j < 3; j++) s.insert(num*factor[j]);
    }
#ifdef DEBUG
    cout << "DEBUG" << endl;
#endif
    cout << "The 1500'th ugly number is " << *s.begin() << "." << endl;
    return 0;
}