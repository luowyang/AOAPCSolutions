/**
 * IP Networks, UVa1590
 * 
 * 注意到32位IP地址可以当成32位无符号整数，只需用掩码和位运算找最长公共前缀即可
 * 事先计算并保存掩码
 * 
 * 注意事项
 * 1.记得初始化变量
 * 2.记得重置变量，避免后效性
 * 3.同一组样例中公共前缀只能变短，不能变长
 * 4.掩码可以是0
**/

#include<stdio.h>
#include<string.h>

unsigned int mask[33] = {0xFFFFFFFF};

unsigned int readIP() {
    char s[33], *sp[4];
    int j = 0;
    unsigned int t, ip = 0;
    scanf("%s", s);
    for (int i = 0; i < 4; i++) {
        sp[i] = &s[j];
        while (s[j] && s[j] != '.') j++;
        s[j++] = '\0';
    }
    for (int i = 0; i < 4; i++) {
        sscanf(sp[i], "%d", &t);
        ip = ip << 8;
        ip += t;
    }
    return ip;
}

int prefix(unsigned int a, unsigned int b, int len) {
    a &= mask[len];
    b &= mask[len];
    while (len < 32 && a != b) {
        a &= mask[++len];
        b &= mask[len];
    }
    return len;
}

void printIP(unsigned int ip) {
    char s[33];
    unsigned int t[4];
    for (int i = 3; i >= 0; i--) {
        t[i] = ip & 0xFF;
        ip = ip >> 8;
    }
    sprintf(s, "%u.%u.%u.%u", t[0], t[1], t[2], t[3]);
    printf("%s\n", s);
}

int main() {
    int m = 1, count = 0, cs = 0;
    for (int i = 1; i <= 32; i++) {
        mask[i] = mask[i-1] - m;
        m = m << 1;
    }
    unsigned int lcp, ip;
    int len;
    while (scanf("%d", &m) == 1) {
        count += (m + 1);
        lcp = readIP(), len = 0;
        while (--m) {
            ip = readIP();
            // printf("DEBUG: IP  = ");
            // printIP(ip);
            len = prefix(lcp, ip, len);
            // printf("DEBUG: len = %d\n", len);
            lcp = mask[len] & lcp;
            // printf("DEBUG: lcp = ");
            // printIP(lcp);
        }
        printIP(lcp);
        printIP(mask[len]);
        cs += 2;
        if (cs == 2098) printf("DEBUG %d\n", count);
    }
    return 0;
}