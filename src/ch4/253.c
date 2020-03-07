/**
 * Cube Painting, UVa253
 * 
 * 暴力解法：算出所有可能的旋转组合下每个位置元素的索引，然后搜索
 * 改进解法：重新按照对面顺序编号，也就是把相对的面连续编号
 * 对面顺序下的旋转相当于交换两对面，并让其中一对内部交换，因此一次交换只能使外逆序改变1，内逆序改变奇数
 * 如果两个立方有不匹配的面对，则必然不等价
 * 如果两个立方有内重复或外重复，必等价
 * 上述两种情况都不成立时，两个立方等价当且仅当内逆序数和外逆序数奇偶相同
 * 
**/

#include<stdio.h>
#include<string.h>
#define maxn 15

char s[maxn];
int marked[3], pos[3];

void reorder() {
    char c1 = s[1], c2 = s[7];
    s[1] = s[5]; s[7] = s[11];
    s[5] = s[4]; s[11] = s[10];
    s[4] = c1; s[10] = c2;
}

int cor(int i, int j, int offset) {
    int r = 0;
    if (s[i<<1] == s[(j<<1)+offset] && s[(i<<1)+1] == s[(j<<1)+1+offset]) r |= 2;
    if (s[(i<<1)+1] == s[(j<<1)+offset] && s[i<<1] == s[(j<<1)+1+offset]) r |= 1;
    return r;
}

int main() {
    while (scanf("%s", s) == 1) {
        reorder();
        //printf("DEBUG: %s\n", s);
        memset(marked, 0, sizeof(marked));
        memset(pos, 0, sizeof(marked));
        int innerRev, outerRev, innerRep;
        innerRev = outerRev = innerRep = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (!marked[j] && cor(i, j, 6)) {
                    marked[j] = cor(i, j, 6);
                    //printf("DEBUG: i=%d j=%d, marked[j]=%d\n", i, j, marked[j]);
                    pos[i] = j;
                    if (marked[j] == 3) innerRep++;
                    if (marked[j]&1) innerRev++;
                    for (int k = 0; k < i; k++) if (pos[k] > j) outerRev++;
                    break;
                }
        int eq = 1;
        for (int i = 0; i < 3 && eq; i++) if (!marked[i]) eq = 0;
        if (!eq) {
            printf("FALSE\n");
            continue;
        }
        int outerRep = 0;
        for (int i = 0; i < 3; i++)
            for (int j = i+1; j < 3; j++)
                if (cor(i, j, 0)) {
                    outerRep++;
                    //printf("DEBUG: i=%d j=%d\n", i, j);
                }
        //printf("DEBUG: ip=%d op=%d\n", innerRep, outerRep);
        if (innerRep || outerRep) {
            printf("TRUE\n");
            continue;
        }
        //printf("DEBUG: ir %d or %d\n", innerRev, outerRev);
        if ((innerRev%2)^(outerRev%2)) printf("FALSE\n");
        else printf("TRUE\n");
    }
    return 0;
}