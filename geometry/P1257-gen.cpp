#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

// [l, r]
long long ra(long long l, long long r) {
    return rnd() % (r - l + 1) + l;
}

int main() {
    int n = ra(2, 10);
    cout << n << endl;
    while (n--) {
        cout << ra(0, 20) << " " << ra(0, 20) << endl;
    }
    return 0;
}
