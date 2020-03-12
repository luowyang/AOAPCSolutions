/**
 * Ducci Sequence, UVa1594
 * Alternative
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 16;
int n, t[maxn];

bool nonZero() {
    for (int i = 0; i < n; i++)
        if (t[i]) return true;
    return false;
}

bool nonLoop() {
    int nz = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (t[i]) {
            if (!nz) nz = t[i];
            else if (t[i] != nz) return true;
        } else {
            cnt++;
        }
    }
    return !nz || !cnt;
}

void ducci() {
    int p = t[0], q;
    for (int i = 0; i < n-1; i++) {
        q = t[i];
        t[i] = abs(t[i]-p);
        p = q;
    }
    t[0] = abs(t[0]-p);
}

void printTup() {
    for (int i = 0; i < n; i++)
        printf("%d ", t[i]);
    cout << "\n";
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> t[i];
        }
        printTup();
        while (nonZero() && nonLoop()) {
            ducci();
            printTup();
        }
        printf("%s\n", nonZero() ? "LOOP" : "ZERO");
    }
    return 0;
}