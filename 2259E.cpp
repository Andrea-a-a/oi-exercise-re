#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> visited(n, false);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        // if (visited[i]) continue;
        if (a[i] > 0) {
            visited[i] = true;
            for (int o = i + 1; o <= n - 1 && o <= i + a[i] - 1; o++) {
                visited[o] = true;
            }
            for (int o = i - 1; o >= 0 && o >= i - a[i] + 1; o--) {
                visited[o] = true;
            }
        }
    }

    // for(auto i : a) cout << "  "<< i;
    // cout << endl;

    // 获得了一个序列，现在判定是否合法
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        if (a[i] != -1)
            b[i] = a[i];
        else {
            if (!visited[i])
                b[i] = 0;
            else
                b[i] = -1;
        }
        // cout << " " << b[i];
    }
    // cout << endl;
    for (int i = 0; i < n; i++) {

        if (b[i] > 0) {
            if ((i + b[i] <= n - 1 && b[i + b[i]] == 0) || (i - b[i] >= 0 && b[i - b[i]] == 0)) {
                continue;
            } else if (i + b[i] >= n && i - b[i] >= 0 && b[i - b[i]] == 0) {
                continue;
            } else if (i - b[i] < 0 && i + b[i] <= n - 1 && b[i + b[i]] == 0) {
                continue;
            }
            cout << "-1\n";
            return;
        } else if (b[i] == 0) {
            if (visited[i]) {
                cout << "-1\n";
                return;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (b[i] == 0) {
            cout << "1";
        } else {
            cout << "0";
        }
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        solve();
    }
    return 0;
}