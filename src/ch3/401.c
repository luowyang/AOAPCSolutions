/**
 * Palindromes, UVa401
**/

#include<stdio.h>
#include<string.h>
#include<ctype.h>

const char rev[] = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const char* msg[] = {"not a palindrome.", "a regular palindrome.", "a mirrored string.", "a mirrored palindrome."};

int main() {
    char s[30];
    while (scanf("%s", s) > 0) {
        int n = strlen(s);
        int i = 0, j = n-1;
        int p = 1, r = 1;
        while (i <= j) {
            if (s[i] != s[j]) p = 0;
            char c = isalpha(s[i]) ? rev[s[i]-'A'] : rev[s[i]-'1'+26];
            if (s[j] != c) r = 0;
            i++;j--;
        }
        printf("%s -- is %s\n\n", s, msg[r*2+p]);
    }
    return 0;
}