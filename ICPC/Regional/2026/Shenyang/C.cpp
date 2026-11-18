#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;

// wa @ 2026/11/18 14:23 死因：INF = 1e10不够大
// wa @ 2026/11/18 14:25 死因：INF = 1e19太大了加一点就溢出了
// ac @ 2026/11/18 14:26

void solve() {
    int n, m, A, B, C;
    cin >> n >> m >> A >> B >> C;
    vector<int> min1(m + 10, INF), lazy(m + 10, 0);
    vector<vector<int>> dp(m + 10, vector<int>(m + 10, INF));
    dp[0][0] = 0;
    min1[0] = 0;
    for (int i = 0; i < n; i++) {
        int req;
        cin >> req;
        int minreq = INF;
        for (int w = 0; w <= m; w++) {
            if (w == req) continue;
            int temp = min1[w];
            // int temp = INF;
            // for (int q = 0; q <= m; q++) {
            //     // if(q == w || q == req)  continue;
            //     temp = min(temp, dp[w][q] + lazy[w]);
            // }
            
            // for (int q = 0; q <= m; q++) {
            //     // if(q == w || q == req)  continue;
            //     temp = min(temp, dp[w][q] );
            // }
            // dp[req]
            //  dp[req][w] = min(min(temp + C, dp[req][w] + A ), min(dp[req][w] + B, dp[w][req] + B));
            dp[req][w] = min(min(temp + C, dp[req][w] + A + lazy[req]), min(dp[req][w] + lazy[req] + B, dp[w][req] + lazy[w] + B)) - lazy[req];
            minreq = min(minreq, dp[req][w]+lazy[req]);
        }
        min1[req] = minreq;
        for (int o = 0; o <= m; o++) {
            if (o == req) continue;
            lazy[o] += A;
            // for(int x = 0; x <= m; x++){
            //     dp[o][x]+=A;
            // }
            min1[o] += A;
        }
    }

    int ans = INF;

    for (int i = 0; i <= m; i++) {
        for (int o = 0; o <= m; o++) {
            ans = min(ans, dp[i][o]+lazy[i]);
        }
    }
    cout << ans << endl;
    return;
}

signed main() {

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}