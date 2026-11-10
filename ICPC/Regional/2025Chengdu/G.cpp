#include <bits/stdc++.h>
using namespace std;

// 30min
// debug: 6min

#define int long long
void solve() {
    int n, k, m;
    cin >> n >> k >> m;
    if (n == 1) {
        cout << 1 << endl;
        return;
    }
    // if(k == 1){
    //     cout << m + 1 + (n-m-1)/2 << endl;
    //     return;
    // }
    // else{
    int cntkm = n / k;
    int cntk = 1;
    int cntelsek = cntkm - 1;
    if (m <= n - cntkm) {
        cntk += m;
    } else {
        cntk = min(m + 1, n);
        cntelsek = n - cntk;
    }
    // cout << "cntkm: " << cntkm << " cntk: " << cntk << endl;

    if (cntelsek >= 2)
        cout << cntk - 1 + (1 + cntelsek + 1) / 2 << endl;
    else
        cout << cntk << endl;
    // }
}

signed main() {

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}