/**
 * Throwing cards away I, UVa10935
**/

#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        queue<int> deck;
        for (int i = 1; i <= n ;i++) deck.push(i);
        cout << "Discarded cards:";
        while (deck.size() > 1) {
            int k = deck.front();
            deck.pop(); deck.push(deck.front()); deck.pop();
            cout << " " << k << (deck.size() > 1 ? "," : "");
        }
        cout << "\nRemaining card: " << deck.front() << "\n";
    }
    return 0;
}