#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define N 100005
#define F(x) (x / 3) + ((x % 3 == 1) ? 0 : tb)
#define G(x) (x < tb ? (x * 3 + 1) : (x - tb) * 3 + 2)
using namespace std;
int wa[N], wb[N];
int wn[N];
bool c12(int * r, int a, int b) {
    return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
}
bool c012(int k, int * r, int a, int b) {
    if (k == 1) {
        return (r[a] < r[b]) || (r[a] == r[b] && wn[a + 1] < wn[b + 1]);
    } else {
        return (r[a] < r[b]) || (r[a] == r[b] && c012(1, r, a + 1, b + 1));
    }
}
void sort(int * r, int * a, int * b, int n, int m) {
    memset(wn, 0, sizeof(wn));
    for (int i = 0; i < n; ++i) {
        wn[r[a[i]]]++;
    }
    for (int i = 1; i < m; ++i) {
        wn[i] += wn[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        b[--wn[r[a[i]]]] = a[i];
    }
}
void dc3(int * r, int * sa, int n, int m) {
    int* rn = r + n, *san = sa + n;
    int tb = (n + 1) / 3;
    r[n] = r[n + 1] = 0;
    int n12 = 0, n0 = 0;
    for (int i = 0; i < n; ++i) {
        if (i % 3 != 0) {
            wa[n12++] = i;
        }
    }
    sort(r + 2, wa, wb, n12, m);
    sort(r + 1, wb, wa, n12, m);
    sort(r, wa, wb, n12, m);
    int p = 1;
    rn[F(wb[0])] = 0;
    for (int i = 1; i < n12; ++i) {
        rn[F(wb[i])] = (c12(r, wb[i - 1], wb[i])? p - 1 : p++);
    }
    if (p == n12) {
        for (int i = 0; i < n12; ++i) {
            san[rn[i]] = i;
        }
    } else {
        dc3(rn, san, n12, p);
    }
    for (int i = 0; i < n12; ++i) {
        if (san[i] < tb) wb[n0++] = san[i] * 3;
    }
    if (n % 3 == 1) wb[n0++] = n - 1;
    sort(r, wb, wa, n0, m);
    for (int i = 0; i < n12; ++i) {
        wb[i] = G(san[i]);
        wn[wb[i]] = i;
    }
    int i, j;
    for (p = 0, i = 0, j = 0; i < n0 && j < n12;) {
        sa[p++] = c012(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
    }
    for (; i < n0; ++i)sa[p++] = wa[i];
    for (; j < n12; ++j)sa[p++] = wb[j];
    for (int i = 0; i < n; ++i) {
        r[i] = wn[i];
    }
}
void calheight (string & s, int * r, int * sa, int n, int * height) {
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (k) k--;
        int j = sa[rank[i] - 1];
        while(i + k < n && j + k < n && s[i + k] == s[j + k])k++;
        height[rank[i]] = k;
    }
}
int main() {
    string s = "helloworld";
    int height[N] = {0};
    int rank[N] = {0};
    for (int i = 0; i < s.size(); ++i) {
        rank[i] = (int)s[i];
    }
    int sa[N] = {0};
    dc3(rank, sa, s.size(), 26);
    calheight(s, rank, sa, s.size(), height);
    return 0;
}
