/**
 * Data Mining, UVa1591
 * 
 * Pi和Qi的关系为Qi=(2^A+1)*Pi/2^B，dP=SP，dQ=Q{i+1}-Qi=(2^A+1)*dP/2^B=(2^A+1)*SP/2^B
 * 为了保证元素不重叠，必须满足SQ<=dQ=(2^A+1)*SP/2^B，即(2^A+1)/2^B>=SQ/SP
 * 所需空间为K=Q{N-1}+SQ=(N-1)*SP*(2^A+1)/2^B+SQ，给定其他参数的情况下K只与(2^A+1)/2^B有关
 * 我们的目标是：保证(2^A+1)/2^B>=SQ/SP的条件下最小化K
 * 
 * 注意事项
 * 1.int会溢出
 * 2.调整算式，避免中间结果溢出
**/

#include<iostream>
using namespace std;
#define infty 0xFFFFFFFFFFFFFFFF
#define maxa 32

int main() {
    unsigned long long n, sp, sq;
    while (cin>> n >> sp >> sq) {
        unsigned long long i, j, a, b, k = infty;
        for (i = 0; i < maxa; i++) {
            for (j = 0; j < maxa; j++) {
                //unsigned long long p = ((sp*(n-1)+((sp*(n-1))<<i))>>j)+sq;
                //printf("DEBUG: i = %I64u j = %I64u p = %I64u k = %I64u\n", i, j, p, k);
                //((sp<<i)+sp) >= (sq<<j) && k > p
                if (((sp + (sp << i)) >= (sq << j)) && (k > ((sp*(n-1)+((sp*(n-1))<<i))>>j)+sq)) {
                    a = i; b = j;
                    k = ((sp*(n-1)+((sp*(n-1))<<i))>>j)+sq;
                }
            }
        }
        printf("%llu %llu %llu\n", k, a, b);
    }
    
    return 0;
}