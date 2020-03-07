/**
 * Hangman Judge, UVa489
 * 
 * 用一个数组记录字符是否存在于答案中且没被猜过，接下来查表即可
 * 此外还需要记录尚未被猜出的字符数和剩下多少次机会
 * 注意维护表格，一旦出结果就及时跳出
**/

#include<stdio.h>
#include<string.h>
#define maxm 30
#define maxn 1005
#define WIN "You win."
#define LOSE "You lose."
#define CO "You chickened out."
#define IND(c) c-'a'

char ans[maxn], guess[maxn];

int main() {
    int mark[maxm];
    int round;
    while (scanf("%d", &round) == 1 && round != -1) {
        memset(mark, 0, sizeof(mark));
        scanf("%s%s", ans, guess);
        int c1 = 0, c2 = 7;
        for (int i = 0; ans[i]; i++) {
            if (!mark[IND(ans[i])]) {
                mark[IND(ans[i])] = 1;
                c1++;
            }
        }
        for (int i = 0; c1 && c2 && guess[i]; i++) {
            if (mark[IND(guess[i])]) {
                mark[IND(guess[i])] = 0;
                c1--;
            } else {
                c2--;
            }
        }
        printf("Round %d\n", round);
        if (!c1) printf("%s\n", WIN);
        else if (!c2) printf("%s\n", LOSE);
        else printf("%s\n", CO);
    }
    return 0;
}