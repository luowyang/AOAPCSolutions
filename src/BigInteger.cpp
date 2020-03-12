/**
 * 大整数类
**/

#include <vector>
#include <list>
#include <string>
#include <iostream>

class BigInteger {
private:
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    std::vector<int> s;     // WARNING: s CANNOT BE EMPTY!
public:
    BigInteger(long long num = 0) { *this = num; }
    BigInteger& operator= (long long num);
    BigInteger& operator= (const std::string& str);
    BigInteger& operator= (const BigInteger& str);
    friend std::ostream& operator<< (std::ostream& out, const BigInteger& x);
    friend std::istream& operator>> (std::istream& in, BigInteger& x);
    BigInteger operator+ (const BigInteger& b);
    BigInteger operator- (const BigInteger& b);
    BigInteger operator* (const BigInteger& b);
    BigInteger operator* (long long num);
    BigInteger operator/ (const BigInteger& b);
    BigInteger& operator+= (const BigInteger& b);
    BigInteger& operator-= (const BigInteger& b);
    bool operator< (const BigInteger& b) const;
    bool operator> (const BigInteger& b) const;
    bool operator== (const BigInteger& b) const;
    bool operator!= (const BigInteger& b) const;
    bool operator<= (const BigInteger& b) const;
    bool operator>= (const BigInteger& b) const;
};

BigInteger& BigInteger::operator= (long long num) {
    s.clear();
    do {
        s.push_back(num % BASE);
        num /= BASE;
    } while (num > 0);
    return *this;
}

BigInteger& BigInteger::operator= (const std::string& str) {
    s.clear();
    int x;
    int len = (str.length() - 1) / WIDTH + 1;
    for (int i = 0; i < len; i++) {
        int end = str.length() - i*WIDTH;
        int start = end - WIDTH > 0 ? end - WIDTH : 0;
        sscanf(str.substr(start, end-start).c_str(), "%d", &x);
        s.push_back(x);
    }
    return *this;
}

BigInteger& BigInteger::operator= (const BigInteger& other) {
    s.clear();
    s.resize(other.s.size());
    for (unsigned int i = 0; i < other.s.size(); i++)
        s[i] = other.s[i];
    return *this;
}

std::ostream& operator<< (std::ostream& out, const BigInteger& x) {
    out << x.s.back();
    for (int i = x.s.size()-2; i >= 0; i--) {
        char buf[20];
        sprintf(buf, "%08d", x.s[i]);
        for (unsigned int j = 0; j < 8; j++) out << buf[j];
    }
    return out;
}

std::istream& operator>> (std::istream& in, BigInteger& x) {
    std::string s;
    if (!(in >> s)) return in;
    x = s;
    return in;
}

BigInteger BigInteger::operator+ (const BigInteger& b) {
    BigInteger c;
    c.s.clear();
    int g = 0;
    for (unsigned int i = 0; g || i < s.size() || i < b.s.size(); i++) {
        int x = g;
        if (i < s.size()) x += s[i];
        if (i < b.s.size()) x += b.s[i];
        c.s.push_back(x % BASE);
        g = x / BASE;
        // std::cout << "+DEBUG c: " << c << "\n";
    }
    return c;
}

BigInteger BigInteger::operator- (const BigInteger& b) {
    BigInteger c;
    c.s.clear();
    int g = 0;
    for (unsigned int i = 0; i < s.size(); i++) {
        int x = s[i] + g;
        if (i < b.s.size()) x -= b.s[i];
        c.s.push_back((x + BASE) % BASE);
        g = x < 0 ? -1 : 0;
    }
    return c;
}

BigInteger BigInteger::operator* (const BigInteger& b) {
    // std::cout << "*DEBUG a: " << *this << "\n";
    // std::cout << "*DEBUG b: " << b << "\n";
    BigInteger c, t;
    long long g;
    for (unsigned int i = 0; i < s.size(); i++) {
        g = 0; t.s.clear();
        t.s.resize(i);
        // printf("*DEBUG t.size: %d\n", t.s.size());
        // std::cout << "*DEBUG t: " << t << "\n";
        for (unsigned int j = 0; j < b.s.size(); j++) {
            long long x = (long long)s[i] * (long long)b.s[j];
            x += g;
            // std::cout << "*DEBUG s[i]: " << s[i] << "\n";
            // std::cout << "*DEBUG b.s[j]: " << b.s[j] << "\n";
            // std::cout << "*DEBUG x: " << x << "\n";
            t.s.push_back(x % BASE);
            g = x / BASE;
            // std::cout << "*DEBUG g: " << g << "\n";
        }
        // std::cout << "*DEBUG t: " << t << "\n";
        c += t;
        // std::cout << "*DEBUG c: " << c << "\n";
    }
    if (g) c.s.push_back(g);
    // std::cout << "*DEBUG c: " << c << "\n";
    return c;
}

BigInteger BigInteger::operator* (long long num) {
    return (*this)*BigInteger(num);
}

BigInteger BigInteger::operator/ (const BigInteger& b) {
    BigInteger c, ta = *this, tb;
    // std::cout << "DEBUG a: " << ta << "\n";
    // std::cout << "DEBUG b: " << tb << "\n";
    int k = s.size() - b.s.size() + 1;
    c.s.resize(k);
    while (k-- && ta != BigInteger(0)) {
        tb.s.resize(k + b.s.size());
        for (int i = 0; i < k; i++) tb.s[i] = 0;
        for (unsigned int i = 0; i < b.s.size(); i++) tb.s[i+k] = b.s[i];
        int x = 0, y = BASE, mid;
        while (x < y) {                 // perform binary search
            mid = (x + y + 1) >> 1;     // mid = (x+y+1)/2 so as to round up
            // printf("DEBUG before x: %d y: %d mid: %d\n", x, y, mid);
            // std::cout << "DEBUG ta: " << ta << "\n";
            // std::cout << "DEBUG tb: " << tb << "\n";
            BigInteger val = tb*mid;
            // std::cout << "DEBUG tb*mid: " << val << "\n";
            if (ta < val) y = mid - 1;
            else { 
                x = mid;
                if (ta == val) y = mid;
            }
            // printf("DEBUG after x: %d y: %d mid: %d\n", x, y, mid);
        }
        ta -= tb*BigInteger(x);
        while (!ta.s.back()) ta.s.pop_back();   // remove leading 0's
        c.s[k] = x;
        // std::cout << "DEBUG c: " << c << "\n";
    }
    while (!c.s.back()) c.s.pop_back();         // remove leading 0's
    // std::cout << "DEBUG c: " << c << "\n";
    return c;
}

BigInteger& BigInteger::operator+= (const BigInteger& b) {
    int g = 0;
    for (unsigned int i = 0; g || i < s.size() || i < b.s.size(); i++) {
        int x = g;
        if (i < s.size()) x += s[i];
        if (i < b.s.size()) x += b.s[i];
        if (i < s.size()) s[i] = x % BASE;
        else s.push_back(x % BASE);
        g = x / BASE;
    }
    return *this;
}

BigInteger& BigInteger::operator-= (const BigInteger& b) {
    int g = 0;
    for (unsigned int i = 0; i < s.size(); i++) {
        int x = s[i] + g;
        if (i < b.s.size()) x -= b.s[i];
        s[i] = (x + BASE) % BASE;
        g = x < 0 ? -1 : 0;
    }
    return *this;
}

bool BigInteger::operator< (const BigInteger& b) const {
    if (s.size() != b.s.size()) return s.size() < b.s.size();
    for (int i = s.size() - 1; i >= 0; i--)
        if (s[i] != b.s[i]) return s[i] < b.s[i];
    return false;
}

bool BigInteger::operator> (const BigInteger& b) const {
    return b < *this;
}

bool BigInteger::operator== (const BigInteger& b) const {
    return s == b.s;
}

bool BigInteger::operator!= (const BigInteger& b) const {
    return s != b.s;
}

bool BigInteger::operator<= (const BigInteger& b) const {
    return !(*this > b);
}

bool BigInteger::operator>= (const BigInteger& b) const {
    return !(*this < b);
}

int main() {
    BigInteger ai, bi, ci;
    std::cin >> ai;
    std::cin >> bi;
    std::cout << ai << "\n";
    std::cout << bi << "\n";
    // std::cout << bi + ci << "\n";
    // ai += bi;
    // std::cout << ai << "\n";
    // std::cout << bi << "\n";
    // std::cout << (ai < bi) << "\n";
    // std::cout << (ai > bi) << "\n";
    // std::cout << (ai >= bi) << "\n";
    // std::cout << (ai <= bi) << "\n";
    // std::cout << (ai == bi) << "\n";
    // std::cout << (ai != bi) << "\n";
    // std::cout << ai - bi << "\n";
    // std::cout << ai * bi << "\n";
    // std::cout << ai * BigInteger(2) << "\n";
    std::cout << ai / bi << "\n";
    return 0;
}