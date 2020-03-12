/**
 * Borrowers, UVa230
**/

#include <set>
#include <map>
#include <string>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

struct book {
    string title, author;
    book(const string& title, const string& author) {
        this->title = title;
        this->author = author;
    }
    bool operator< (const book& b) const {
        return author < b.author || (author == b.author && title < b.title);
    }
    friend ostream& operator<< (ostream& out, const book& b) {
        out << "title: " << b.title << " , author: " << b.author;
        return out;
    }
};

void parseBook(const string& buf, string& title, string& author) {
    int i, j;
    for (i = 0; buf[i] != '"'; i++);
    for (j = i+1; buf[j] != '"'; j++);
    title = buf.substr(i, ++j);
    for (i = j; buf[i] != 'y'; i++);
    for (i++; buf[i] == ' '; i++);
    author = buf.substr(i);
}

void parseInst(const string& buf, string& title) {
    int i, j;
    for (i = 0; buf[i] != '"'; i++);
    for (j = i+1; buf[j] != '"'; j++);
    title = buf.substr(i, ++j);
}

int main() {
    set<book> shelf, returned;
    map<string, string> tta;
    string buf, s, t;
    while (getline(cin, buf) && buf != "END") {
        parseBook(buf, s, t);
        book b(s, t);
        if (shelf.count(b)) continue;
        shelf.insert(book(s, t));
        tta.insert({s, t});
    }
    while (cin >> buf && buf != "END") {
        if (buf[0] == 'S') {
            // for (auto const& b : shelf) cout << "DEBUG shelf " << b << "\n";
            // for (auto const& b : returned) cout << "DEBUG returned " << b << "\n";
            set<book>::iterator it;
            for (auto const &b : returned) {
                // cout << "DEBUG b " << b << "\n";
                shelf.insert(b);
                it = shelf.find(b);
                cout << "Put " << b.title << " ";
                if (it == shelf.begin()) cout << "first";
                else { it--; cout << "after " << it->title; }
                cout << "\n";
            }
            cout << "END\n";
            returned.clear();
        } else {
            getline(cin, s);
            parseInst(s, t);
            if (buf[0] == 'B') shelf.erase(book(t, tta[t]));
            else returned.insert(book(t, tta[t]));
        }

    }
    return 0;
}