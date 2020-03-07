/**
 * Message Decoding, UVa213
 * 
 * 编码可以记录在一张解码表中，码字长度不超过7因此只需256个表项
 * 解码表的索引和码字间的映射关系是：长为k的码字前有2^k-2项，内部有序
 * 注意全1对应的项是结束符
 * 另一个问题是编码串可能分布在不同行，需要编写函数特别处理
**/

#include<stdio.h>
#include<string.h>
#define maxm 256

char code[maxm];

char readChar() {
    char c;
    while ((c=getchar()) == '\n' || c == '\r' || c ==' ' || c == '\t');
    return c;
}

int readInt(int len) {
    int n = 0;
    while (len--) n = (n<<1) + readChar() - '0';
    return n;
}

int readHead() {
    memset(code, 0, sizeof(code));
    char c = readChar();
    int i = 0, k = 1;
    while (i < maxm && c != '\n') {
        if (c == EOF) return 0;
        code[i] = c;
        c = getchar();
        if (++i == k) {
            i++;
            k = ((k+3)<<1)-3;
        }
    }
    return 1;
}

int main() {
    while (readHead()) {
        while (1) {
            int len = readInt(3);
            if (!len) break;
            int k = (1<<len)-2;
            char ch;
            while (1) {
                ch = code[readInt(len) + k];
                if (!ch) break;
                putchar(ch);
            }
        }
        printf("\n");
    }
    return 0;
}