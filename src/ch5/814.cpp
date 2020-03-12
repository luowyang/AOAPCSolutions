/**
 * The Letter Carrier's Rounds, UVa814
 * 
 * 用set保存所有的地址（用户名+MTA），对输入的每一条信息，把目的MTA顺序保存在vector里，把每个MTA的目的地址保存在set里，把这些set放进map里
 * 
 * 注意事项
 * 1.注意用getchar()吃掉换行符
 * 2.只有一个目的MTA中至少存在一个合法用户时才启动DATA
 * 3.注意用set在目标地址中去重
**/

#include <set>
#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;

void parseAddr(const string& s, string& user, string& mta) {
    int k = s.find('@');
    user = s.substr(0, k);
    mta = s.substr(k+1);
}

int main() {
    set<string> addr;
    string s, t, mtaSrc, userSrc, mtaDest, userDest;
    int k;
    // read MTA list
    while (cin >> s && s != "*") {
        cin >> s >> k;
        while (k--) { cin >> t; addr.insert(t + "@" + s); }
    }
    while (cin >> s && s != "*") {
        // parse source address
        parseAddr(s, userSrc, mtaSrc);
        // process address
        vector<string> mta;                     // MTAs to contact
        map<string, vector<string> > dest;      // destination users in each MTA
        set<string> visited;                    // set of visited users
        while (cin >> t && t != "*") {
            // parse destination address
            if (visited.count(t)) continue;
            visited.insert(t);
            parseAddr(t, userDest, mtaDest);
            if (!dest.count(mtaDest)) { mta.push_back(mtaDest); dest[mtaDest] = vector<string>(); }
            dest[mtaDest].push_back(t);
        }
        getchar();
        // read and build data, notice the indents
        string data;
        while (getline(cin, t) && t != "*") data += "     " + t + "\n";
        // contact each MTA
        for (int i = 0; i < mta.size(); i++) {
            mtaDest = mta[i]; vector<string> users = dest[mtaDest];
            cout << "Connection between " << mtaSrc << " and " << mtaDest << "\n";
            cout << "     HELO " << mtaSrc << "\n"; cout << "     250\n";
            cout << "     MAIL FROM:<" << s << ">\n"; cout << "     250\n";
            bool ok = false;
            for (int i = 0; i < users.size(); i++) {
                cout << "     RCPT TO:<" << users[i] << ">\n";
                if (addr.count(users[i])) { ok = true; cout << "     250\n"; }
                else cout << "     550\n";
            }
            if (ok) cout << "     DATA\n     354\n" << data << "     .\n     250\n";
            cout << "     QUIT\n     221\n";
        }
    }
    return 0;
}