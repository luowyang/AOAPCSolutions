/**
 * Tex Quotes, UVa 272
**/
#include<stdio.h>

int main() {
    char c;
    int flag = 0;
    while ((c = getchar()) != EOF) {
        if (c == '"') {
            printf("%s", flag ? "''" : "``");
            flag = !flag;
        } else {
            printf("%c", c);
        }
    }
    return 0;
}