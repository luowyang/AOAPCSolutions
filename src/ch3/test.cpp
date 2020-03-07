#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;
void Cal(double m, int e, double esp) { //一种暴力解法，仅供参考
    double mv, ev;
    for (int M = 0; M <= 9; ++M) {
        mv = 1 - pow(2, -(M + 1));
        for (int E = 1; E <= 30; ++E) {
            ev = pow(2, E) - 1;
            if (abs(log(mv) + ev * log(2) - (log(m) + e * log(10))) < esp) {
                cout << M << " " << E << endl;
                return;
            }
        }
    }
}

int main() {
    const double esp = 1e-5;
    string fpn, sm, se;
    double m, e;
    while (cin >> fpn && fpn != "0e0") {
        sm = fpn.substr(0, 17);
        se =  fpn.substr(18, fpn.length() - 18);
        istringstream issm(sm);
        issm >> setprecision(15) >> m;
        stringstream isse(se);
        isse >> e;
        Cal(m, e, esp);
    }
    return 0;
}