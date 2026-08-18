#include <bits/stdc++.h>
using namespace std;

int n, m, k;


void solve(){
   
    cin >> n >> m >> k; 
    vector<bool> able(n+1, true);
    vector<vector<int>> g(n+1);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    vector<int> q(k+1);
    for(int i = 1; i <= k; i++){
        cin >> q[i];
        able[q[i]] = false;
    }

    vector<bool> reach(n+1, false);
    reach[1] = true;

    //判断YES
    queue<int> que;
    bool yess = false;
    que.push(1);
    while(!que.empty() && !yess ){
        int u = que.front();
        que.pop();
        for(auto v : g[u]){
            if(!reach[v]){
                reach[v] = 1;
                if(v == n){
                    yess = true;
                    break;
                }
                if(able[v]) que.push(v);
            }
        }
    }

    if(yess){
        cout << "YES" << endl;
        return;
    }

    queue<int> que2;
    int ans = -1;

    for(int i = k; i >= 1; i--){
        int x = q[i];
        able[x] = true;
        if(reach[x]){
            que2.push(x);
        }

        while(!que2.empty()){
            int u = que2.front(); que2.pop();
            for(auto v : g[u]){
                if(!reach[v]){
                    reach[v] = true;
                    if(v == n){
                        ans = i-1;
                        cout << ans << endl;
                        return;
                    }
                    if(able[v]){
                        que2.push(v);
                    }
                }
            }
        }
    }

    if(ans == -1){
        cout << "NO" << endl;
    }


}

int main(){

    ios::sync_with_stdio(0); cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}