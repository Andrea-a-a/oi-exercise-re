#include <bits/stdc++.h>
using namespace std;

// 13 min!
#define int long long
// debug: 2min

void solve(int n) {
    // int sqr = n/2;
    // //cout << "meow" << n << sqr << endl;
    // if(n == 1){
    //     cout << "NO" << endl;
    //     return;
    // }
    // for (int i = 1; i <= sqr; i++) {
    //     if (n % i == 0 && n % (n - i) == 0) {
    //         cout << "YES\n"
    //              << i << " " << n - i << "\n";
    //         return;
    //     }
    // }
    if (n % 2 == 0) {
        cout << "Yes" << endl
             << n / 2 << " " << n / 2 << endl;
        return;
    }
    cout << "No" << endl;
    return;
}

signed main() {

    int T;
    cin >> T;
    // for(int i = 1; i <= T; i++){
    //     solve(i);
    // }
    while (T--) {
        int n;
        cin >> n;
        solve(n);
    }
}