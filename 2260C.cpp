#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long x, y;
        cin >> x >> y;

        long long S = x + y; 
        long long X = x;

        long long bestA;



        if ((X | S) == S) {
            bestA = X;
        } else {
            // Find highest bit where x has 1 but S has 0
            int p = -1;
            for (int bit = 60; bit >= 0; --bit) {
                if ((X & (1LL << bit)) && !(S & (1LL << bit))) {
                    p = bit;
                    break;
                }
            }


            long long high = (X >> (p + 1)) << (p + 1);
            long long low = S & ((1LL << p) - 1);

            bestA = high | low;
        }

        long long ans = X - bestA;

        cout << S << ' ' << ans << '\n';
    }

    return 0;
}