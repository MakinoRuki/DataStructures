#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define N 100005
using namespace std;
int n, m;
int type;
vector<int> edges[N];
int son[N], par[N], sz[N];
int dep[N];
int idx[N];
int top[N];
int cnt;
struct node {
    int idx, l, r;
    int val;
};
node tree[4*N];
void dfs1 (int u, int p) {
    sz[u] = 1;
    par[u] = p;
    for (int i = 0; i < edges[u].size(); ++i) {
        int v = edges[u][i];
        if (v == p) continue;
        dfs1(v, u);
        if (son[u] == -1 || sz[v] > sz[son[u]]) {
            son[u] = v;
        }
        sz[u] += sz[v];
    }
}
void dfs2 (int u, int p, int tp, int d) {
    dep[u] = d;
    idx[u] = ++cnt;
    top[u] = tp;
    if (son[u] >= 0) dfs2(son[u], u, tp, d + 1);
    for (int i = 0; i < edges[u].size(); ++i) {
        int v = edges[u][i];
        if (v != p && v != son[u]) {
            dfs2(v, u, v, d + 1);
        }
    }
}
void build (int root, int l, int r) {
    tree[root].l = l;
    tree[root].r = r;
    tree[root].val = 0;
    if (l == r) return;
    int mid = (l + r) / 2;
    build(root * 2, l, mid);
    build(root * 2 + 1, mid + 1, r);
}
void insert (int root, int idx, int val) {
    if (tree[root].l == idx && tree[root].r == idx) {
        tree[root].val += val;
        return;
    }
    int mid = (tree[root].l + tree[root].r) / 2;
    if (idx <= mid) insert(root * 2, idx, val);
    else insert(root * 2 + 1, idx, val);
    tree[root].val = tree[root * 2].val + tree[root * 2 + 1].val;
}
int query (int root, int l, int r) {
    if (tree[root].l == l && tree[root].r == r) {
        return tree[root].val;
    }
    int mid = (tree[root].l + tree[root].r) / 2;
    if (r <= mid) return query(root * 2, l, r);
    else if (l > mid) return query(root * 2 + 1, l, r);
    else return query(root * 2, l, mid) + query(root * 2 + 1, mid + 1, r);
}
int solve (int u, int v) {
    int res = 0;
    while(true) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        if (top[u] == top[v]) {
            if (u == v) return res;
            if (dep[u] < dep[v]) swap(u, v);
            int tmp = query(1, idx[son[v]], idx[u]);
            if (tmp) return -1;
            return res + idx[u] - idx[v];
        }
        int tmp = query(1, idx[top[u]], idx[u]);
        if (tmp) return -1;
        res += idx[u] - idx[top[u]] + 1;
        u = par[top[u]];
    }
    return res;
}
int main() {
    scanf("%d", &n);
    int u, v, e;
    vector<pair<int, int> > tmpes;
    for (int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        edges[u].push_back(v);
        edges[v].push_back(u);
        tmpes.push_back(make_pair(u, v));
    }
    memset(sz, 0, sizeof(sz));
    memset(son, -1, sizeof(son));
    cnt = 0;
    dfs1(1, 0);
    dfs2(1, 0, 1, 0);
    build(1, 1, n);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &type);
        if (type == 3) {
            scanf("%d%d", &u, &v);
            printf("%d\n", solve(u, v));
        } else {
            scanf("%d", &e);
            u = tmpes[e - 1].first;
            v = tmpes[e - 1].second;
            if (dep[u] < dep[v]) swap(u, v);
            if (type == 1) insert(1, idx[u], -1);
            else insert(1, idx[u], 1);
        }
    }
    return 0;
}
