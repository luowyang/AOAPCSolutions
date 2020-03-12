/**
 * Revenge of Fibonacci, UVa12333
**/

#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;

#define maxn 5000005
#define maxf 100000
#define maxd 41

struct fib {
    static const int BASE = 10;
    static const int LIM = 120;
    int v[LIM] = {0}, len = 0;
    fib() { *this = 1; }
    fib& operator= (long long num) {
        len = 0;
        do {
            v[len++] = num % BASE;
            num /= BASE;
        } while (num);
        return *this;
    }
    fib& operator+= (fib& b) {
        if (len == LIM) {
            len = LIM >> 1; b.len = b.len - (LIM >> 1);
            for (int i = 0; i < len; i++)  v[i] = v[i+len];
            for (int i = 0; i < b.len; i++)  b.v[i] = b.v[i+len];
        }
        int c = 0;
        for (int i = 0; i < len || i < b.len || c; i++) {
            if (i < len) c += v[i];
            if (i < b.len) c += b.v[i];
            // printf("DEBUG c = %d, v[%d] = %d, b.v[%d] = %d\n", c, i, v[i], i, b.v[i]);
            if (i < len) v[i] = c % BASE;
            else v[len++] = c % BASE;
            c /= BASE;
        }
        return *this;
    }
    friend ostream& operator<< (ostream& out, const fib& f) {
        for (int i = f.len-1; i >= 0; i--)
            out << f.v[i];
        return out;
    }
};

int trie[maxn][10], val[maxn], N = 1;

void insert(const fib& f, int n) {
    int cur = 0, next;
    for (int i = f.len-1, cnt = 0; i >= 0 && cnt < maxd; i--, cnt++) {
        next = trie[cur][f.v[i]];
        if (!next) { 
            trie[cur][f.v[i]] = next = N++;
            val[next] = n;
        }
        cur = next;
    }
}

int query(char buf[]) {
    int cur = 0;
    for (int i = 0; buf[i]; i++) {
        cur = trie[cur][buf[i]-'0'];
        if (!cur) return -1;
    }
    return val[cur];
}

int main() {
    fib f[2];
    int i = 0, j = 1;
    insert(f[0], 0); insert(f[1], 1);
    for (int n = 2; n < maxf; n++) {
        f[i] += f[j];
        insert(f[i], n);
        // cout << "DEBUG fib(" << n-1 << ") = " << f[i] << "\n";
        i = 1 - i; j = 1 - j;
        // cout << "DEBUG N: " << N << "\n";
        // if (n == 100000 || n == 100001) cout << "DEBUG fib(" << n-1 << ") = " << f[i] << "\n";
    }
    int T, kase = 0;
    char buf[maxd];
    scanf("%d", &T);
    while (T--) {
        scanf("%s", buf);
        printf("Case #%d: %d\n", ++kase, query(buf));
    }
    return 0;
}