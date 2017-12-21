#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define N 100005
using namespace std;
int mod = 51061;
int n, m;
int rev[N];
int son[N][2];
int fa[N];
void addValue(int x, int mulv, int plusv) {
    if (x < 0) return;
    v[x] = (v[x] * mulv + plusv) % mod;
    val[x] = (val[x] * mulv + plusv * size[x]) % mod;
    mul[x] = (mul[x] * mulv) % mod;
    plus[x] = (plus[x] * mulv + plusv) % mod;
}
void pushUp(int x) {
    val[x] = (val[son[x][0]] + val[son[x][1]] + v[x]) % mod;
    size[x] = size[son[x][0]] + size[son[x][1]] + 1;
}
void pushDown(int x) {
    if (rev[x]) {
        rev[son[x][0]] ^= 1;
        rev[son[x][1]] ^= 1;
        swap(son[x][0], son[x][1]);
        rev[x] = 0;
    }
    if (mul[x] > 1) {
        addValue(son[x][0], mul[x], 0);
        addValue(son[x][1], mul[x], 0);
        mul[x] = 1;
    }
    if (plus[x] > 0) {
        addValue(son[x][0], 1, plus[x]);
        addValue(son[x][1], 1, plus[x]);
        plus[x] = 0;
    }
}
void rotate(int x) {
    int y = fa[x];
    if (y == -1) return;
    int yx = (son[y][0] != x);
    int z = fa[y];
    fa[x] = z;
    fa[y] = x;
    fa[son[x][yx ^ 1]] = y;
    son[y][yx] = son[x][yx ^ 1];
    son[x][yx ^ 1] = y;
    son[z][yx] = x;
    pushUp(y);
    pushUp(x);
}
void splay(int x) {
    vector<int> stack;
    stack.clear();
    for (int i = fa[x]; i != -1; i = fa[i]) stack.push_back(i);
    for (int i = stack.size() - 1; i >= 0; --i) pushDown(stack[i]);
    int y = fa[x];
    int z = fa[y];
    while(y != -1) {
        if (z != -1) {
            int zy = (son[z][0] != y);
            int yx = (son[y][0] != x);
            if (zy == yx) {
                rotate(x); rotate(x);
            } else {
                rotate(y); rotate(x);
            }
        } else {
            rotate(x);
        }
    }
}
void access(int x) {
    int rs = -1;
    while(fa[x] >= 0) {
        splay(x);
        son[x][1] = rs;
        rs = x;
        x = fa[x];
    }
}
void moveRoot(int x) {
    access(x);
    splay(x);
    rev[x] ^= 1;
}
void link(int x) {
    moveRoot(x);
    fa[y] = x;
}
void cut(int x) {
    moveRoot(x);
    access(y);
    splay(y);
    son[y][0] = -1;
    fa[x] = -1;
}
int main() {
    int x, y, z;
    int a, b;
    cin>>n>>m;
    memset(rev, 0, sizeof(rev));
    memset(fa, -1, sizeof(fa));
    for (int i = 1; i <= n; ++i) {
        size[i] = 1;
    }
    for (int i = 1; i < n; ++i) {
        cin>>x>>y;
        link(x, y);
    }
    for (int i = 0; i < m; ++i) {
        string s;
        cin>>s;
        if (s[0] == '+') {
            cin>>x>>y>>z;
            moveRoot(x);
            access(y);
            splay(y);
            addValue(y, 1, z);
        } else if (s[0] == '-') {
            cin>>x>>y>>a>>b;
            cut(x, y);
            link(a, b);
        } else if (s[0] == '*') {
            cin>>x>>y>>z;
            moveRoot(x);
            access(y);
            splay(y);
            addValue(y, z, 0);
        } else if (s[0] == '/') {
            cin>>x>>y;
            moveRoot(x);
            access(y);
            splay(y);
            cout<<val[y]<<endl;
        }
    }
    return 0;
}
