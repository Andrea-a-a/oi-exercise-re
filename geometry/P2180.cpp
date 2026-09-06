#include <bits/stdc++.h>
using namespace std;

signed main() {
    long long N, M, K;
    cin >> N >> M >> K;

    if (N > M) swap(N, M);
    long long k = sqrt(K), m = K / k;
    if (m > N) {
        m = N;
        k = K / m;
    }

    cout << k * (k - 1) * m * (m - 1) / 4;

    return 0;
}