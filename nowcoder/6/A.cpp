//并查集，压缩路径
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+10;
int fa[MAXN], sz[MAXN];
//int id[MAXN];
const int MOD = 998244353;

int find(int x){
    if(fa[x] == x)  return x;
    else{
        
        return fa[x] = find(fa[x]);
    }
}

void merge(int x, int y){
    int ry = find(y), rx = find(x);
    
    sz[ry] = sz[rx] + sz[ry];
    sz[ry] %= MOD;
    fa[rx] = ry;
}


// void ini(){
//     memset(fa, 0, sizeof(fa));
//     memset(sz, 0, sizeof(sz));

// }

void solve(){
    // ini();
    long long ans = 1;

    int n;
    cin >> n;
    vector<int> p(n), ind(n+1);
    for(int i = 0; i < n; i++){
        cin >> p[i];
        fa[p[i]] = p[i];
        ind[p[i]] = i;
        sz[p[i]] = 1;
    }

    //从大（n）到小（1）开始考虑
    for(int i = n; i >= 1; i--){
            int rti = find(i);
            ans *= sz[rti];
            ans %= MOD;
            sz[rti]--;
        if(ind[i] - 1 >= 0 && ind[i] + 1 <= n-1 && sz[find(p[ind[i]-1])] > 0 && sz[find(p[ind[i]+1])] > 0){
            merge(p[ind[i]-1], p[ind[i]+1]);

        }

    }

    cout << ans << endl;


}


int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
