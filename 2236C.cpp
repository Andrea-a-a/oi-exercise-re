#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        sort(a.begin(), a.end());

        // 分组：相同值合并
        vector<int> vals, cnts;
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && a[j] == a[i]) ++j;
            vals.push_back(a[i]);
            cnts.push_back(j - i);
            i = j;
        }

        int m = vals.size();
        vector<bool> win(m, false);
        // nextFalse[i] 表示从 i 开始（包括 i）第一个 win 为 false 的索引，若不存在则为 m
        vector<int> nextFalse(m + 1, m);
        nextFalse[m] = m;

        for (int i = m - 1; i >= 0; --i) {
            // 二分找到最大的 R 使得 vals[R] <= vals[i] + k
            int R = upper_bound(vals.begin(), vals.end(), vals[i] + k) - vals.begin() - 1;
            bool hasFalse = false;
            if (i + 1 <= R) {
                if (nextFalse[i + 1] <= R) hasFalse = true;
            }
            if (hasFalse) {
                win[i] = true;
            } else {
                win[i] = (cnts[i] % 2 == 0);
            }
            nextFalse[i] = (win[i] ? nextFalse[i + 1] : i);
        }

        bool ok = false;
        for (int i = 0; i < m; ++i) {
            if (win[i]) {
                ok = true;
                break;
            }
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}