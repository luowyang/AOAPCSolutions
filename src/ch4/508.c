/**
 * Morse Mismatches, UVa508
 * 
 * 解法1：建立词的码表，再按输入顺序匹配
 * 
 * 解法2：字典树
 * 先建码表，再读字典建字典树，最后再字典树中匹配，分为三种情况：完美匹配，最长前缀元素，最短额外元素
 * 用二叉字典树记录字典的编码，二叉字典树用一个二维数组、一个结点数组
 * 用一个二维数组记录字典树，其第一维索引是结点编号，第二维索引是子结点编号，.是0，-是1，值是子结点编号
 * 用一个字符串数组记录码表，索引是字符
 * 用一个字符串数组记录字典词，同时需要配一个重复次数数组，用来判断是否需要输出!
 * 
 * 注意事项
 * 1.对于有相同摩尔斯码的词，只保留最先出现的，同时要记录有几个词有相同的摩尔斯码
**/

#include<stdio.h>
#include<string.h>
#define maxt 20000
#define maxa 150
#define maxm 12
#define maxd 150
#define maxn 100
#define ind(c) (c=='.'?0:1)

int trie[maxt][2], node[maxt], count[maxd], N, wlen[maxd];
char alpha[maxa][maxm], dict[maxd][maxn];

void insert(int k) {
    char s[maxn], *p = s;
    for (int i = 0; dict[k][i]; i++) {
        strcpy(p, alpha[(unsigned char)dict[k][i]]);
        while (*p) p++;
    }
    wlen[k] = strlen(s);
    int n = 0, m;
    for (int i = 0; s[i]; i++) {
        m = ind(s[i]);
        if (!trie[n][m]) trie[n][m] = ++N;
        n = trie[n][m];
    }
    if (!node[n]) node[n] = k;
    count[node[n]]++;
    // printf("DEBUG: %s(id:%d) = %s\n", dict[k], n, s);
}

void printTrie(int n) {
    if (node[n]) printf("(%s)", dict[node[n]]);
    else printf("(%d)", n);
    if (trie[n][0]) printTrie(trie[n][0]);
    else printf("()");
    if (trie[n][1]) printTrie(trie[n][1]);
    else printf("()");
}

int prefix(char *s) {
    int n = 0, m, pre = 0;
    for (int i = 0; s[i]; i++) {
        m = ind(s[i]);
        n = trie[n][m];
        if (!n) break;
        if (node[n]) pre = n;
    }
    return pre;
}

void suffix(int k, int len, int *suf, int *slen) {
    if (!k || len > *slen) return;
    if (node[k] && len <= *slen) { *suf = k; *slen = len; return; }
    if (trie[k][0]) suffix(trie[k][0], len+1, suf, slen);
    if (trie[k][1]) suffix(trie[k][1], len+1, suf, slen);
}

int main() {
    unsigned char chs[2];
    while (scanf("%s", chs) && chs[0] != '*') {
        scanf("%s", alpha[chs[0]]);
    }
    int k = 1;
    while (scanf("%s", dict[k]) && dict[k][0] != '*') {
        insert(k);
        k++;
    }
    char s[maxn];
    while (scanf("%s", s) && s[0] != '*') {
        int n = 0, m;
        for (int i = 0; s[i]; i++) {
            m = ind(s[i]);
            n = trie[n][m];
            if (!n) break;
        }
        if (n && node[n]) { printf("%s%s\n", dict[node[n]], count[node[n]]>1?"!":""); continue; }
        int pre, plen, suf, slen, len = strlen(s);
        pre = suf = 0; slen = 0x7FFFFFFF;
        pre = prefix(s); plen = pre ? wlen[node[pre]] : 0xFFFFFFFF;
        suffix(n, len, &suf, &slen); slen = suf ? wlen[node[suf]] : 0x7FFFFFFF;
        // printf("DEBUG: prefix = %s, suffix = %s\n", dict[node[pre]], dict[node[suf]]);
        printf("%s?\n", (len-plen)<=(slen-len)?dict[node[pre]]:dict[node[suf]]);
    }
    return 0;
}