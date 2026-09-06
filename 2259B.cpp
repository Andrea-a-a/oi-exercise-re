#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    int odd = 0, two = 0, zero = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        long long w;
        cin >> w;
        if (w % 2 == 1)
            odd++;
        else if (w % 4 == 0)
            zero++;
        else
            two++;
    }
    cout << max(two, max(odd, zero)) << endl;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        solve();
    }
    return 0;
}