#include <bits/stdc++.h>
using namespace std;

//  9min!
// debug: 1min

void solve() {
    int n, k, m, b;
    cin >> n >> m >> k >> b;
    // vector<int> sum, sumr;
    int cntb = 0, cnta = 0;
    for (int i = 0; i < n; i++) {
        vector<int> scr(m);
        int s1 = 0, s2 = 0;
        for (int o = 0; o < m; o++) {
            cin >> scr[o];
            s1 += scr[o];
            if (scr[o] >= 1) {
                s2 += scr[o] - 1;
            } else {
                s2 += scr[o] + 1;
            }
        }
        if (s1 >= k)
            cntb++;
        else {
            if (s2 >= k) cnta++;
        }
    }
    cout << cntb + min(cnta, b) << endl;
}

signed main() {

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}