/**
 * WERTYU, UVa10082
**/

#include<stdio.h>

char cs[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";

int main() {
    int c;
    while ((c = getchar()) != EOF) {
        int i;
        for (i = 0; cs[i] && cs[i] != c; i++);
        if (cs[i]) putchar(cs[i-1]);
        else       putchar(c);
    }
    return 0;
}