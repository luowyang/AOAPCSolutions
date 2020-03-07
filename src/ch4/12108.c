/**
 * Extraordinarily Tired Students, UVa12108
 * 
 * 注意到下一时刻的状态只与当前时刻有关
 * 用一个一维数组记录当前时刻的状态，根据当前状态更新下一时刻状态，模拟睡觉过程
 * 
 * 注意事项
 * 1.可能并不存在“全部都清醒”的时刻
 * 2.只要有超过一半学生醒着就一定存在“全部都清醒”的时刻
 * 3.如果在某个时刻回到初始状态，则不存在“全部都清醒”的时刻
 * 4.记得重置变量！！！
**/

#include<stdio.h>
#include<string.h>
#define maxn 11

int period[maxn][2], state[maxn], init[maxn], N, T, asleep;

void printState() {
    printf("T%2d (awaken%2d asleep%2d): ", T, N-asleep, asleep);
    for (int i = 0; i < N; i++)
        if (state[i] <= period[i][0]) printf(" %2d  ", state[i]);
        else printf("(%2d) ", state[i]);
    printf("\n");
}

int simultate() {
    int loop = 0;
    int stop = asleep == 0 ? 1 : 0;
    // printState();
    while (!loop && !stop) {
        T++; asleep <<= 1;
        loop = 1; stop = 1;
        int a = 0;
        for (int i = 0; i < N; i++) {
            if (state[i] == period[i][0])
                state[i] = asleep > N ? state[i] + 1 : 1;
            else state[i] = state[i] == period[i][1] ? 1 : state[i] + 1;
            if (state[i] > period[i][0]) { a++; stop = 0; }
            if (state[i] != init[i]) loop = 0;
        }
        asleep = a;
        // printState();
    }
    return stop;
}

int main() {
    int kase = 0;
    while (scanf("%d", &N) == 1 && N) {
        T = 1; asleep = 0;
        for (int i = 0; i < N; i++) {
            scanf("%d%d%d", &period[i][0], &period[i][1], &state[i]);
            period[i][1] += period[i][0];
            if (state[i] > period[i][0]) asleep++;
            init[i] = state[i];
        }
        // printf("Case %d: \n", ++kase);
        printf("Case %d: ", ++kase);
        if(simultate()) printf("%d\n", T);
        else printf("-1\n");
    }
    return 0;
}