#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#define N 502
#define M 1002
#define chr 130
using namespace std;
int n, m;
int ans[M][5];
bool vis[N];
int tot;
struct node {
    int cnt;
    node* fail;
    struct node* next[chr];
    node() {
        fail = NULL;
        for (int i = 0; i < chr; ++i) {
            next[i] = NULL;
        }
        cnt = -1;
    }
};
void insert(node* root, string & s, int idx) {
    node* cur = root;
    for (int i = 0; i < s.size(); ++i) {
        if (cur->next[s[i] - 'a'] == NULL) {
            cur->next[s[i] - 'a'] = new node();
        }
        cur = cur->next[s[i] - 'a'];
    }
    cur->cnt = idx;
}
void getfail(node* root) {
    queue<node*> q;
    q.push(root);
    root->fail = root;
    while(!q.empty()) {
        node* cur = q.front();
        q.pop();
        for (int i = 0; i < chr; ++i) {
            if (cur->next[i] != NULL) {
                node* pre = cur->fail;
                while(pre != root && pre->next[i] == NULL) {
                    pre = pre->fail;
                }
                if (pre != root) {
                    cur->next[i]->fail = pre->next[i];
                } else {
                    cur->next[i]->fail = root;
                }
                q.push(cur->next[i]);
            }
        }
    }
}
void query(node* root, string& s, int idx) {
    node* cur = root;
    for (int i = 0; i < s.size(); ++i) {
        while(cur != root && cur->next[s[i] - 'a'] == NULL) {
            cur = cur->fail;
        }
        if (cur->next[s[i] - 'a'] != NULL) {
            cur = cur->next[s[i] - 'a'];
        }
        node* pre = cur;
        while(pre != root) {
            if (pre->cnt >= 0) {
                if (!vis[pre->cnt]) {
                    ++ans[idx][0];
                    ans[idx][ans[idx][0]] = pre->cnt;
                    vis[pre->cnt] = true;
                }
            }
            pre = pre->fail;
        }
    }
}
int main() {
    string s;
    node* root = new node();
    cin>>n;
    for (int i = 0; i < n; ++i) {
        cin>>s;
        insert(root, s, i);
    }
    getfail(root);
    tot = 0;
    cin>>m;
    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < m; ++i) {
        cin>>s;
        memset(vis, false, sizeof(vis));
        query(root, s, i);
        tot += (ans[i][0] > 0);
        if (ans[i][0] > 0) {
            cout<<"web "<<i + 1<<":";
            for (int j = 1; j <= ans[i][0]; ++j) {
                cout<<" "<<ans[i][j] + 1;
            }
            cout<<endl;
        }
    }
    if (tot) {
        cout<<"total: "<<tot<<endl;
    }
    return 0;
}
