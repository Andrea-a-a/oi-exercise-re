#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<ll> a(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> a[i];

        vector<int> can(n + 1, 0);
        for (int i = 0; i < m; i++) {
            int x;
            cin >> x;
            can[x] = 1;
        }

        ll dp0 = 0, dp1 = LLONG_MIN / 4;

        for (int i = n; i >= 1; i--) {
            ll ndp0, ndp1;

            if (can[i]) {
                ndp0 = a[i] + max(dp0, dp1);
                ndp1 = -a[i] + max(dp0, dp1);
            } else {
                ndp0 = a[i] + dp0;
                ndp1 = -a[i] + dp1;
            }

            dp0 = ndp0;
            dp1 = ndp1;
        }

        cout << dp0 << '\n';
    }

    return 0;
}