#include <bits/stdc++.h>
using namespace std;

const long long M = 998244353;
void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    map<pair<int, int>, long long> g;
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        if(u > v)   swap(u, v);
        if(g.find({u, v}) != g.end()){
            g[{u, v}]++;
        }
        else{
            g[{u, v}] =1;
        }
    }

    if(k != 2) { cout << "0" << endl; return;}

    long long ans = 0;
    for (auto &[edge, cnt] : g) {
        if(cnt == 1)    continue;
        else{
            ans = (ans + ((cnt * (cnt-1)/2)) % M) % M;
        }
    }

    cout << ans << endl;
    
}

int main(){

    ios::sync_with_stdio(false); cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        solve();
    }



    return 0;
}