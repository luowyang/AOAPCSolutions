/**
 * Printer Queue, UVa12100
**/

#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;

const int maxn = 105;

int main() {
    int T, n, m, k, p[maxn];
    cin >> T;
    while (T--) {
        priority_queue<int, vector<int> > pq;
        queue<int> q;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> k; p[i] = k;
            pq.push(k); q.push(i);
        } 
        int t = 0;
        while (true) {
            k = q.front(); q.pop();
            // printf("DEBUG t = %d p[k] = %d pq.top() = %d\n", t, p[k], pq.top());
            if (p[k] == pq.top()) {
                pq.pop(); t++;
                if (k == m) break;
            } else {
                q.push(k);
            }
        }
        cout << t << "\n";
    }
    return 0;
}