/**
 * Andy's First Dictionary, UVa10815
 * 
 * 用一个set记录输入中不同的词，输入时一次读入一个字符串，移除其中所有标点（替换成空格）并转换成小写，然后用stringstream读
 * 
 * 注意事项
 * 1.不要写错变量名
**/

#include <set>
#include <string>
#include <sstream>
#include <iostream>
#include <cctype>
using namespace std;

int main() {
    string s, buf;
    set<string> dict;
    while (cin >> s) {
        for (string::iterator i = s.begin(); i != s.end(); i++)
            if (isalpha(*i)) *i = tolower(*i); else *i = ' ';
        stringstream ss(s);
        while (ss >> buf) dict.insert(buf);
    }
    for (string a : dict) cout << a << endl;
    return 0;
}