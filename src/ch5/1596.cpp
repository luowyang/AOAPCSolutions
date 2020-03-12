/**
 * Bug Hunt, UVa1596
**/

#include <map>
#include <string>
#include <cctype>
#include <cstdio>
#include <iostream>
using namespace std;

map<string, map<int, int> > st;
map<string, int> sz;

void readInt(const string& s, int &d) {
    int i;
    for (i = 0; isdigit(s[i]); i++);
    sscanf(s.c_str(), "%d", &d);
}

bool evaluate(const string& s, int& d) {
    int i;
    for (i = 0; !isalpha(s[i]) && !isdigit(s[i]); i++);
    if (isdigit(s[i])) { readInt(&s[i], d); return true; }
    string sym;
    int c, safe;
    for (; isalpha(s[i]); i++) sym.push_back(s[i]);
    while (s[i] != '[') i++;
    safe = evaluate(s.substr(i+1), c);
    if (!safe || !sz.count(sym) || sz[sym] <= c || !st[sym].count(c)) return false;
    d = st[sym][c];
    return true;
}

// parse a[exp] to get a and the value of exp
void parseLeft(string& s, string& sym, int& c) {
    int i;
    for (i = 0; !isalpha(s[i]); i++);
    for (; isalpha(s[i]); i++) sym.push_back(s[i]);
    while (s[i] != '[') i++;
    evaluate(s.substr(i+1), c);
}

int main() {
    string buf;
    while (getline(cin, buf) && buf[0] != '.') {
        // cout << "DEBUG buf: " << buf << "\n";
        st.clear(); sz.clear();
        int c, d, error = 0, cnt = 0;
        while (buf[0] != '.') {
            cnt++;
            string s, t, sym;
            int k = buf.find('=');
            parseLeft(buf, sym, c);
            // cout << "DEBUG sym: " << sym << " c: " << c << "\n";
            if (k < buf.length()) {
                t = buf.substr(k+1);
                if (!evaluate(t, d) || !sz.count(sym) || sz[sym] <= c) 
                { error = cnt; break; }
                if (!st[sym].count(c)) st[sym].insert({c, 0});
                st[sym][c] = d;
            } else {
                st.insert({sym, map<int, int>()});
                sz.insert({sym, c});
            }
            getline(cin, buf);
            // cout << "DEBUG buf: " << buf << "\n";
        }
        cout << error << "\n";
        if (error)
            while (getline(cin, buf) && buf[0] != '.');
                // cout << "DEBUG buf: " << buf << "\n";
    }
    return 0;
}