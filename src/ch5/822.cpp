/**
 * Queue and A, UVa822
**/

#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

struct event {
    int num, wait, t, dt;
    event() {}
    event(int num, int t0, int t, int dt) : num(num), wait(t0), t(t), dt(dt) {}
};

struct agent {
    int pid, k, tbegin = 0, tend = 0;
    vector<int> pq;
    agent(int pid, int k) : pid(pid), k(k) {}
    bool operator< (const agent& b) const {
        return tbegin < b.tbegin || (tbegin == b.tbegin && pid < b.pid);
    }
    friend ostream& operator<<(ostream& out, const agent& a) {
        out << "pid = " << a.pid << " tbegin = " << a.tbegin << " tend = " << a.tend;
        return out;
    }
};

const int infty = 0x7FFFFFFF;

int main() {
    int n, m, kase = 0;
    while (cin >> n && n) {
        map<int, event> topic;
        vector<agent> person;
        int tt, num, t0, t, dt;
        for (int i = 0; i < n; i++) {
            cin >> tt >> num >> t0 >> t >> dt;
            topic.insert({tt, event(num, t0, t, dt)});
        }
        cin >> m;
        int pp, k;
        while (m--) {
            cin >> pp >> k;
            person.push_back(agent(pp, k));
            while (k--) {
                cin >> tt;
                person[person.size()-1].pq.push_back(tt);
            }
        }
        int tcur, tnext = 0;
        while (tnext < infty) {     // continue if there are still unprocessed event
            tcur = tnext;
            // printf("DEBUG tcur %d\n", tcur);
            tnext = infty;
            sort(person.begin(), person.end());
            for (auto &p : person) {
                // cout << "DEBUG p " << p << "\n";
                if (p.tend > tcur) { tnext = min(tnext, p.tend); continue; }    // busy agent should continue his work
                for (auto t: p.pq) {
                    if (!topic[t].num) continue;
                    if (topic[t].wait <= tcur) {    // top waiting event has arrived
                        p.tbegin = tcur; p.tend = tcur + topic[t].t;
                        topic[t].num--;
                        if (topic[t].num) topic[t].wait += topic[t].dt;
                        else n--;                   // finish a topic
                        tnext = min(tnext, p.tend);
                        // printf("DEBUG agent %d begin %d at %d end %d\n", p.pid, t, p.tbegin, p.tend);
                        break;
                    }
                }
            }
            for (auto &t : topic) {
                if (!t.second.num) continue;
                if (t.second.wait > tcur) tnext = min(tnext, t.second.wait);
                // printf("DEBUG event %d is waiting at %d (%d left)\n", t.first, t.second.wait, t.second.num);
            }
        }
        printf("Scenario %d: All requests are serviced within %d minutes.\n", ++kase, tcur);
    }
    return 0;
}