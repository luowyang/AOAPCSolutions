#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int k = n; k >= 1; k--) {
        for (int i = 0; i < n-k; i++)
            printf(" ");
        for (int i = 0; i < 2*k-1; i++)
            printf("#");
        printf("\n");
    }
    return 0;
}