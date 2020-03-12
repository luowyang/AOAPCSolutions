/**
 * Ananagrams, UVa156
 * 
 * 用一个map，键是转换成小写并给字符排好序的输入字符串，值是出现次数
 * 用一个set记录原字符串
 * 
 * 注意事项
 * 1.不要滥用指针
**/

#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <cctype>
using namespace std;

string proc(const string &s) {
    string ans = s;
    for (int i = 0; i < s.size(); i++) ans[i] = tolower(s[i]);
    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    map<string, int> dict;
    set<string> word;
    string s;
    while (cin >> s && s[0] != '#') {
        word.insert(s);
        string r = proc(s);
        map<string, int>::iterator it = dict.find(r);
        if (it == dict.end()) {
            dict.insert(make_pair(r, 1));
        } else {
            it->second++;
        }
    }
    for (auto &a : word) {
        string r = proc(a);
        if (dict[r] == 1) cout << a << endl;
    }
    return 0;
}