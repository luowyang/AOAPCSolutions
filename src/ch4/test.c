#include<stdio.h>
#include<stdlib.h>

char c = 'c';

void swap(int a, int b) {
    int t = a;
    a = b;
    b = t;
}

char * const * test() {
    printf("test called\n");
    char* const* h = &c;
    return h;
}

int main() {
    char *const *(*next)() = test;
    next();
    int a = 3, b = 4;
    swap(a, b);
    printf("a=%d b=%d", a, b);
    return 0;
}