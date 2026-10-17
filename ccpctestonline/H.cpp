#include <bits/stdc++.h>
using namespace std;

struct Tree {
    int n;
    vector<vector<int>> ver, val;
    vector<int> lg, dep;
    Tree(int n) {
        this->n = n;
        ver.resize(n + 1);
        val.resize(n + 1, vector<int>(30));
        lg.resize(n + 1);
        dep.resize(n + 1);
        for (int i = 1; i <= n; i++) { //预处理 log
            lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
        }
    }
    void add(int x, int y) { // 建立双向边
        ver[x].push_back(y);
        ver[y].push_back(x);
    }
    void dfs(int x, int fa) {
        val[x][0] = fa; // 储存 x 的父节点
        dep[x] = dep[fa] + 1;
        for (int i = 1; i <= lg[dep[x]]; i++) {
            val[x][i] = val[val[x][i - 1]][i - 1];
        }
        for (auto y : ver[x]) {
            if (y == fa) continue;
            dfs(y, x);
        }
    }
    int lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        while (dep[x] > dep[y]) {
            x = val[x][lg[dep[x] - dep[y]] - 1];
        }
                if (x == y) return x;
        for (int k = lg[dep[x]] - 1; k >= 0; k--) {
            if (val[x][k] == val[y][k]) continue;
            x = val[x][k];
            y = val[y][k];
        }
        return val[x][0];
    }
    int clac(int x, int y) { // 倍增查询两点间距离
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }
    void work(int root = 1) { // 在此初始化
        dfs(root, 0);
    }
};

int main(){
    int op;
    cin >> op;
    if(op == 1){
        int n;
        cin >> n;
        if(n == 1){
            int p;
            cin >> p;
            cout << n << endl;
            cout << endl;
            cout << p << endl;
        }
        else{
            cout << n << endl;
            vector<int> p(n-1), a(n);
            for(int i = 0; i < n-1; i++){
                cin>> p[i];
            }
            for(int i = 0; i < n; i++){
                cin >> a[i];
            }
            for(int u : p)  cout << u << " ";
            cout << endl;
            for(int u : a)  cout << u << " ";
            cout << endl;
        }
    }
    else if(op==2){
        
        int n;
        cin >> n;
        if(n == 1){
            int x;
            cin >> x;
            int q;
            cin >> q;
            while(q--){
                int u, v;
                cin >> u >> v;
                cout << x << " " << "1" << endl;
            }
        }
        else{
            vector<int> p(n+1, 0), a(n+1, 0);
            Tree tr(n);

            for(int i = 2; i <= n; i++){
                cin>> p[i];
                tr.add(i, p[i]);
            }
            tr.work();
            for(int i = 1; i <= n; i++){
                cin >> a[i];
            }
            int q;
            cin >> q;
            while(q--){
                
                int u, v;
                cin >> u >> v;
                int mn = 1e9+10;
                int cnt = 0;
                int lca = tr.lca(u, v);
                //cout << "lca: " << lca;
                //u -> lca
                int c = u;
                while(c != lca){
                    //cout << " cons: " << c << endl;
                    if(a[c] < mn){
                        mn = a[c];
                        cnt = 1;
                    }
                    else if(a[c] == mn)  cnt++;
                    c = p[c];
                }
                int d = v;
                while(d != lca){
                    //cout << " cons: " << d << endl;
                    if(a[d] < mn){
                        mn = a[d];
                        cnt = 1;
                    }
                    else if(a[d] == mn)  cnt++;
                    d = p[d];
                }
                if(a[lca] < mn){
                    mn = a[lca];
                    cnt = 1;
                }
                else if(a[lca] == mn)   cnt++;
                
                cout << mn << " " << cnt << endl;

            }
        }
    }
}

/*
 * 5
 * 154 156 689 48815 2288926 
*/