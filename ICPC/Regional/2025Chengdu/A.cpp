#include <bits/stdc++.h>
using namespace std;
// 想了半个小时发现自己不会
// 神奇哉

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int r(int a, int b) {
    return rnd() % (b - a + 1) + a;
}
long long ma = 0, mi = 400;

void gen(int n) {
    vector<int> a(n), b(n), c(n);
    long long s = 0, s2 = 0;
    for (int i = 0; i < n; i++) {
        a[i] = r(1, 1000);
        s += a[i];
    }
    for (int i = 0; i < n; i++) {
        b[i] = round(100.0 * a[i] / s);
        s2 += b[i];

        // cout << b[i] << " ";
    }
    ma = max(s2, ma);
    mi = min(s2, mi);
    // cout << s2 << endl;
    for (int i = 0; i < n; i++) {
        c[i] = round(100.0 * b[i] / s2);
        // cout << c[i] << " ";
        //  if(c[i] != b[i]){
        //      cerr << "NONONO! at index = "<< i << " " << endl;
        //      for(auto w : a) cout << w << " ";
        //      cout << endl;
        //      for(auto w : b) cout << w << " ";
        //      cout << s2 << endl;
        //  }
    }
    // cout << endl<< endl;
}

void solve(){
    
}

int main() {
    // cout << round(114.514);
    // cout << fixed << setprecision(2) << 1.14514 << endl;
    int T;
    cin >> T;
    while (T--) {
        // int p = r(1,20);
        //  p %= 100;
        // gen(400);
        // cout << p%100 << endl;
    }
    // cout << "max: " << ma << " min: " << mi;
    return 0;
}