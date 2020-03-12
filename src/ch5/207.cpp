/**
 * PGA Tour Prize Money, UVa207
 * 
 * 用一个数组保存奖金表，用一个结构体数组保存选手信息，包括名字和每轮的成绩
 * 用自定义的比较函数对索引数组进行排序，把犯规处理成无穷大，使得犯规选手自动有序
 * 第一次排序后指出排名前70的选手
 * 第二次对上次指出的选手排序，然后按照规则计算奖金
 * 
 * 注意事项
 * 1.第一次getline前要用getchar吃掉换行符
 * 2.用两个指针处理排名相同的区间
 * 3.第一轮排名时，并列70名要算进去
 * 4.第二轮排名时，只要超过70名就不发奖金（设为isAma即可），但是仍然要算排名
 * 5.eps不要取太大
**/

#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define INFTY 10000
#define PLAYER(i) players[ids[i]]
#define half(i) (players[ids[i]].half)
#define total(i) (players[ids[i]].total)
#define isAma(i) (players[ids[i]].isAma)
#define isDQ(i) (players[ids[i]].total>=INFTY)
#define name(i) (players[ids[i]].name)
#define eps 1e-8

struct player {
    string name;
    bool isAma;
    int score[4], half, total;
    player& operator= (string& s) {
        name = s.substr(0, 20);
        isAma = false;
        for (int i = 0; i < 20; i++) if (name[i] == '*') isAma = true;
        // cout << "DEBUG iaAma = " << isAma << "\n";
        int p = 20, isDQ = 0; while (s[p] == ' ') p++;
        for (int i = 0; i < 4; i++) {
            if (s[p] == 'D') isDQ = 1;
            if (isDQ) score[i] = INFTY;
            else {
                sscanf(s.substr(p, 2).c_str(), "%d", &score[i]);
                p += 3;
            }
        }
        // for (int i = 0; i < 4; i++) printf("DEBUG score[%d] = %d\n", i, score[i]);
        half = score[0] + score[1];
        total = half + score[2] + score[3];
        // printf("DEBUG half: %d total: %d\n", half, total);
        return *this;
    }
};

const int maxn = 145, maxp = 70;
double prz, prizes[maxp], share[maxn];
player players[maxn];
int ids[maxn], n, last, cntp[maxn], cntt[maxn];

bool lessHalf(const int i, const int j) {
    if (players[i].half != players[j].half) return players[i].half < players[j].half;
    return players[i].name < players[j].name;
}

bool lessTotal(const int i, const int j) {
    if (players[i].total != players[j].total) return players[i].total < players[j].total;
    return players[i].name < players[j].name;
}

int main() {
    int T, first = 1;
    cin >> T;
    string buf;
    while (T--) {
        // input
        cin >> prz;
        for (int i = 0; i < maxp; i++) cin >> prizes[i];
        cin >> n; getchar();
        for (int i = 0; i < n; i++) {
            getline(cin, buf);
            players[i] = buf;
            ids[i] = i;
        }

        // sorting
        sort(ids, ids+n, lessHalf);
        // for (int i = 0; i < n; i++) printf("DEBUG ids[%d] = %d, player[%d].half = %d\n", i, ids[i], ids[i], half(i));
        int r = 0;
        // for (last = 0; last < n && r < maxp && half(last) < INFTY; last++)
            // if (!last || half(last-1) < half(last)) r++;
        for (last = 0; last < n && last < maxp && half(last) < INFTY; last++);
        while (last < n && half(last-1) == half(last)) last++;
        // printf("DEBUG: after\n");
        // for (int i = 0; i < last; i++) printf("DEBUG ids[%d] = %d, player[%d].half = %d\n", i, ids[i], ids[i], half(i));
        sort(ids, ids+last, lessTotal);
        // printf("DEBUG: after2\n");
        // for (int i = 0; i < last; i++) printf("DEBUG ids[%d] = %d, player[%d].total = %d\n", i, ids[i], ids[i], players[ids[i]].total);
        
        // processing
        int a, b, pcnt, tcnt, exhausted;
        r = a = exhausted = 0;
        while (a < last && !isDQ(a)) {
            pcnt = tcnt = 0;
            for (b = a; total(b) == total(a) && b < last; b++) {
                if (!isAma(b)) pcnt++;
                tcnt++;
            }
            double pt = 0.0;
            int rt;
            // printf("DEBUG r: %d ", r);
            for (rt = r; rt-r < pcnt && rt < maxp; rt++) pt += prizes[rt];
            // printf(" rt: %d pt: %.2lf\n", rt, pt);
            if (pcnt) pt = pt*prz/100.0/pcnt + eps;
            r = rt;
            for (; a != b; a++) { cntp[a] = pcnt; cntt[a] = tcnt; share[a] = pt; if (exhausted) PLAYER(a).isAma = true; }
            if (r >= maxp) exhausted = 1;
        }
        // for (int i = 0; i < last; i++) printf("DEBUG cntt[%d] = %d, cntp[%d] = %d\n", i, cntt[i], i, cntp[i]);
        int cnt = 1, t;
        for (int i = 0; i < last; i++) {
            t = cntt[i]; cntt[i] = cnt;
            if (total(i) < total(i+1)) cnt += t;
            // printf("DEBUG t = %d, cnt = %d, cntt[%d] = %d\n", t, cnt, i, cntt[i]);
        }

        // output
        if (first) first = 0;
        else printf("\n");
        printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n");
        printf("-----------------------------------------------------------------------\n");
        char buf[15];
        bool ama, isDQ;
        for (int i = 0; i < last; i++) {
            ama = PLAYER(i).isAma; isDQ = isDQ(i);
            cout << name(i); printf(" ");
            sprintf(buf, "%d%s", cntt[i], cntp[i]>1 && !ama? "T" : "");
            printf("%-10s", isDQ ? "" : buf);
            for (int j = 0; j < 4; j++)
                if (PLAYER(i).score[j] < INFTY) printf("%-5d", PLAYER(i).score[j]);
                else printf("     ");
            if (isDQ) printf("DQ");
            else if (ama) printf("%-3d", PLAYER(i).total);
            else printf("%-10d", PLAYER(i).total);
            if (!isDQ && !ama) printf("$%9.2lf", share[i]);
            printf("\n");
        }
    }
    return 0;
}