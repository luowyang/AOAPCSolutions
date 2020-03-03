#include<stdio.h>

int main() {
    for (int a = 1; a <= 9; a++) {
        for (int b = 1; b <= 9; b++) {
            if (b == a) continue;
            for (int c = 1; c <= 9; c++) {
                if (c == a || c == b) continue;
                int i = a*100 + b*10 + c;
                int j = 2*i;
                int k = 3*i;
                if (k > 987) break;
                if (j/100 == a || (j%100)/10 == a || j%10 == a) continue;
                if (j/100 == b || (j%100)/10 == b || j%10 == b) continue;
                if (j/100 == c || (j%100)/10 == c || j%10 == c) continue;
                if (k/100 == a || (k%100)/10 == a || k%10 == a) continue;
                if (k/100 == b || (k%100)/10 == b || k%10 == b) continue;
                if (k/100 == c || (k%100)/10 == c || k%10 == c) continue;
                printf("%d %d %d\n", i, j, k);
            }
        }
    }
    return 0;
}