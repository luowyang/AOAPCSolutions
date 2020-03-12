/**
 * Use of Hospital Facilities, UVa212
**/

#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define free 0
#define use 1
#define prep 2
#define infty 0x7FFFFFFF

struct patient {
    string name;
    int rt, bt, begin, rn, bn;
};

struct facility {
    int pn = 0, begin = 0, end = 0, state = free, total = 0;
};

string formatTime(int mnt, int T) {
    T += (mnt / 60);
    mnt %= 60;
    char buf[10];
    sprintf(buf, "%2d:%02d", T, mnt);
    return string(buf);
}

int main() {
    int n, m, T, t1, t2, t3, k, top;
    while (cin >> n >> m >> T >> t1 >> t2 >> t3 >> k) {
        top = 1;
        vector<patient> pat(k+1);
        vector<facility> room(n+1), bed(m+1);
        for (int i = 1; i <= k; i++) {
            pat.push_back(patient());
            cin >> pat[i].name >> pat[i].rt >> pat[i].bt;
        }
        int cur, next = 0;
        while (next < infty) {
            cur = next; next = infty;
            // printf("DEBUG cur = %d\n", cur);
            for (int i = 1; i <= n; i++) {
                // printf("DEBUG room[%d].end = %d\n", i, room[i].end);
                if (room[i].end > cur) { next = min(next, room[i].end); continue; }
                if (room[i].state == use) {
                    // prepare room
                    room[i].state = prep; room[i].begin = cur; room[i].end = cur + t2;
                    next = min(next, room[i].end);
                    // move patient to bed
                    int p = room[i].pn;
                    for (int j = 1; j <= m; j++) {
                        // printf("DEBUG bed[%d] state = %d begin = %d end = %d\n", j, bed[j].state, bed[j].begin, bed[j].end);
                        if (bed[j].end > cur) continue;
                        if (bed[j].state == use) {
                            bed[j].state = prep; bed[j].begin = bed[j].end; bed[j].end += t3;
                            if (bed[j].end > cur) continue;    // beds will need tome to prepare
                        }
                        if (bed[j].state == prep) {
                            bed[j].state = free; bed[j].begin = bed[j].end;
                        }
                        if (bed[j].state == free) {
                            bed[j].state = use; bed[j].total += pat[p].bt;
                            bed[j].begin = cur + t1; bed[j].end = bed[j].begin + pat[p].bt;
                            pat[p].bn = j;
                            // printf("DEBUG bed[%d] updated state = %d begin = %d end = %d\n", j, bed[j].state, bed[j].begin, bed[j].end);
                            // printf("DEBUG patient %d begin to use the bed %d\n", p, j);
                            break;
                        }
                        // printf("DEBUG bed[%d] updated state = %d begin = %d end = %d\n", j, bed[j].state, bed[j].begin, bed[j].end);
                    }
                } else if (room[i].state == prep) {
                    // free room
                    room[i].state = free; room[i].begin = cur;
                }
                if (room[i].state == free && top <= k) {
                    // use room
                    room[i].pn = top; room[i].state = use;
                    room[i].begin = cur; room[i].end = cur + pat[top].rt;
                    room[i].total += pat[top].rt;
                    next = min(next, room[i].end);
                    // move patient to room
                    pat[top].rn = i; pat[top].begin = cur;
                    top++;
                }
            }
        }
        // output table 1
        printf(" Patient          Operating Room          Recovery Room\n");
        printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n");
        printf(" ------------------------------------------------------\n");
        int total = 0;
        for (int i = 1; i <= k; i++) {
            int time = pat[i].begin;
            string rb = formatTime(time, T), re = formatTime(time+=pat[i].rt, T);
            string bb = formatTime(time+=t1, T), be = formatTime(time+=pat[i].bt, T);
            total = max(total, time);
            printf("%2d  %-10s%2d   %s   %s     %2d   %s   %s\n", i, pat[i].name.c_str(), pat[i].rn, rb.c_str(), re.c_str(), pat[i].bn, bb.c_str(), be.c_str());
        }
        // output table 2
        printf("\nFacility Utilization\nType  # Minutes  %% Used\n-------------------------\n");
        for (int i = 1; i <= n; i++) {
            printf("Room %2d%8d   %5.2lf\n", i, room[i].total, room[i].total*100.0/total);
        }
        for (int i = 1; i <= m; i++) {
            printf("Bed  %2d%8d   %5.2lf\n", i, bed[i].total, bed[i].total*100.0/total);
        }
        printf("\n");
    }
    return 0;
}