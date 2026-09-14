//暴力
#include <bits/stdc++.h>
using namespace std;

const int M = 998244353;

long long frac[200010];
long long rev[200010];

long long qpow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}


long long f1(int l, int m, int k){
    int N = l + k - 1 - (k - 1) * m;   
    if (N < 0 || N < m || m < 0) return 0;  
    return frac[N] * rev[m] % M * rev[N - m] % M;
}

long long f2(int l, int k){
    if(l <= 0)   return 1;
    int maxm = (l-1)/k + 1;
    long long ans = 0;
    for(int i = 0; i <= maxm; i++){
        ans = (ans + f1(l, i, k) % M) % M;
    }
    return ans;
}

void solve(){
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < q; i++){
        int x, k;
        cin >> x >> k;
        long long ans = (f2(n, k) - f2(x-k, k) * f2(n-x-k+1, k) % M + M) % M;
        cout << ans << endl;
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);

    //初始化阶乘
    frac[0] = 1;
    for(int i = 1; i <= 200001; i++){
        frac[i] = ((frac[i-1] % M) * i) % M;
    }

    rev[200001] = qpow(frac[200001], M - 2);


    for (int i = 200001; i >= 1; i--) {
        rev[i-1] = rev[i] * i % M;
    }

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}