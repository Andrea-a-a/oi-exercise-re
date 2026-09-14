#include <bits/stdc++.h>
using namespace std;

long long p[62];

void insert(long long x){
    for(int i = 61; i >= 0; i--){
        if((x >> i) == 0){
            continue;
        }
        else if(p[i] == 0){
            p[i] = x;
            return;
        }
        else{
            x = x ^ p[i];
        }
    }
}


void solve(){
   // memset(a, 0, sizeof(a));
    memset(p, 0, sizeof(p));
    int n, len, q;
    cin >> n >> len >> q;
    vector<long long> a(n+1, 0);
    
    vector<long long> pre(n+1, 0);
    
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        pre[i] = pre[i-1] ^ a[i];

    }

    for(int i = 1; i + len - 1 <= n; i++){
        insert(pre[i+len-1] ^ pre[i-1]);
    }

    while(q--){
        long long x;
        cin >> x;
        long long ans = x;
    
        for(int i = 61; i >= 0; i--){
            ans = max(ans, ans ^ p[i]);
        }
        cout << ans << '\n';
    }

}


int main(){

    ios::sync_with_stdio(false); cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    
    return 0;
}