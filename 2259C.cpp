#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;

    int minus = 0, one = 0, zero = 0;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 0)
            zero++;
        else if (a[i] == 1)
            one++;
        else if (a[i] == -1)
            minus++;
    }
    if (minus == 0) {
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
        return;
    }

    int index1 = -1, index2 = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) {
            break;
        }
        if (a[i] == -1) {
            a[i] = 1;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == 1) {
            break;
        }
        if (a[i] == -1) {
            a[i] = 1;
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        if (a[i] != -1)
            cout << a[i] << " ";
        else
            cout << "0 ";
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