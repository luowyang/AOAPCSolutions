#include<stdio.h>
#include<stdlib.h>
#include<math.h>

char* bin(void* d, int n) {
    char* b = (char*) malloc(sizeof(char) * (n+1));
    int i;
    unsigned long long* p = (unsigned long long *) d;
    b[n] = '\0';
    for (i = n-1; i >= 0; i--) {
        b[i] = '0' + (*p & 0x1);
        *p = *p >> 1;
    }
    return b;
}

int main() {
    int i = 1/0;
    int t = i;
    char* b = bin((void*)&t, 32);
    printf("%s\n", b);
    printf("%d\n", i);
    printf("%u\n", i);
    return 0;
}