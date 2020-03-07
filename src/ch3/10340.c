/**
 * All in All, UVa10340
 * 
 * 用一个指针i指向s中正在比较的字符，用一个指针j指向t中正在比较的字符
 * 每比较一个字符就j++，如果发现s[i]==t[j]就i++
**/

#include<stdio.h>
#define maxn 1000005

char s[maxn];
char t[maxn];

int main() {
    while (scanf("%s%s", s, t) > 1) {
        int i, j;
        for (i = j = 0; s[i] && t[j]; j++)
            if (s[i] == t[j]) i++;
        printf("%s\n", s[i] ? "No" : "Yes");   
    }
    return 0;
}