/**
 * Urban Elevations, UVa221
**/

#include <set>
#include <string>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define NINFTY (-1e10)

const int maxn = 105;

struct building {
    int tag;
    double x, y, w, h;
    bool operator< (const building& b) const {
        return x < b.x || (x == b.x && y < b.y);
    }
    double right() {
        return x + w;
    }
} b[maxn];

struct cmp {
    int index;
    bool operator< (const cmp& other) const {
        return b[index].y < b[other.index].y || (b[index].y == b[other.index].y && index < other.index);
    }
    cmp(int i) { index = i; }
};

struct endpoint {
    int index;
    bool left;
    double x, y;
    bool operator< (const endpoint& other) const {
        return x < other.x || (x == other.x && y < other.y) || (x == other.x && y == other.y && left);
    }
} ep[2*maxn];

int n;

int main() {
    int kase = 0;
    for (int i = 0; i < maxn; i++) b[i].tag = i + 1;
    while (cin >> n && n) {
        double t;
        for (int i = 0, j = 0; i < n; i++, j += 2) {
            cin >> b[i].x >> b[i].y >> b[i].w >> t >> b[i].h;
            ep[j].index = i; ep[j].x = b[i].x; ep[j].y = b[i].y; ep[j].left = true;
            ep[j+1].index = i; ep[j+1].x = b[i].x+b[i].w; ep[j+1].y = b[i].y; ep[j+1].left = false;
        }
        sort(ep, ep+(n<<1));
        set<cmp> scan;
        set<building> visible;
        double m;
        for (int i = 0, j = 1; i < (n<<1); ) {
            double r = ep[i].x;
            set<cmp>::iterator it;
            for (j = i + 1; j < (n<<1) && ep[j].x == r; j++);
            for (; i < j; i++) {
                if (ep[i].left) scan.insert(cmp(ep[i].index));
                else scan.erase(scan.find(cmp(ep[i].index)));
            }
            m = NINFTY;
            for (it = scan.begin(); it != scan.end(); it++) {
                if (b[it->index].h > m && b[it->index].right() > r) {
                    m = b[it->index].h;
                    visible.insert(b[it->index]);
                }
            }
        }
        if (kase) printf("\n");
        printf("For map #%d, the visible buildings are numbered as follows:\n", ++kase);
        int first = 1;
        for (auto &v : visible) {
            if (first) first = 0; else printf(" ");
            printf("%d", v.tag);
        }
        printf("\n");
    }
    return 0;
}