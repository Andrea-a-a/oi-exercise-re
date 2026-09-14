#include <bits/stdc++.h>
using namespace std;

void solve() {

    long long x, y, k;
    cin >> x >> y >> k;
    long long ans = 0;
    for (int i = 0; i < k;) {
        if((y + i) / (x + i) != (y+i-1) / (x + i-1) || i == 0)    cout << " at " << i << " th month, get " << (y + i) % (x + i) << "  y / x =" << (y + i) / (x + i) << " ans: "<< ans << endl;

        ans += (y + i) % (x + i);
        i++;
    }
    cout << ans << endl;
}
/*

 at 0 th month, get 0y / x =1
0
 at 0 th month, get 1y / x =3
 at 1 th month, get 3y / x =2
0
 at 0 th month, get 2y / x =2
 at 1 th month, get 1y / x =2
 at 2 th month, get 0y / x =2
 at 3 th month, get 5y / x =1
 at 4 th month, get 5y / x =1
 at 5 th month, get 5y / x =1
18
 at 0 th month, get 6y / x =2
0
 at 0 th month, get 5y / x =2
 at 1 th month, get 4y / x =2
 at 2 th month, get 3y / x =2
 at 3 th month, get 2y / x =2
 at 4 th month, get 1y / x =2
 at 5 th month, get 0y / x =2
 at 6 th month, get 15y / x =1
 at 7 th month, get 15y / x =1
 at 8 th month, get 15y / x =1
 at 9 th month, get 15y / x =1
 at 10 th month, get 15y / x =1
 at 11 th month, get 15y / x =1
 at 12 th month, get 15y / x =1
 at 13 th month, get 15y / x =1
 at 14 th month, get 15y / x =1
 at 15 th month, get 15y / x =1
 at 16 th month, get 15y / x =1
 at 17 th month, get 15y / x =1
 at 18 th month, get 15y / x =1
 at 19 th month, get 15y / x =1
 at 20 th month, get 15y / x =1
 at 21 th month, get 15y / x =1
 at 22 th month, get 15y / x =1
 at 23 th month, get 15y / x =1
 at 24 th month, get 15y / x =1
 at 25 th month, get 15y / x =1
 at 26 th month, get 15y / x =1
 at 27 th month, get 15y / x =1
 at 28 th month, get 15y / x =1
 at 29 th month, get 15y / x =1
 at 30 th month, get 15y / x =1
 at 31 th month, get 15y / x =1
 at 32 th month, get 15y / x =1
 at 33 th month, get 15y / x =1
 at 34 th month, get 15y / x =1
 at 35 th month, get 15y / x =1
 at 36 th month, get 15y / x =1
 at 37 th month, get 15y / x =1
 at 38 th month, get 15y / x =1
 at 39 th month, get 15y / x =1
 at 40 th month, get 15y / x =1
 at 41 th month, get 15y / x =1
 at 42 th month, get 15y / x =1
 at 43 th month, get 15y / x =1
 at 44 th month, get 15y / x =1
 at 45 th month, get 15y / x =1
 at 46 th month, get 15y / x =1
 at 47 th month, get 15y / x =1
 at 48 th month, get 15y / x =1
 at 49 th month, get 15y / x =1
 at 50 th month, get 15y / x =1
 at 51 th month, get 15y / x =1
 at 52 th month, get 15y / x =1
 at 53 th month, get 15y / x =1
 at 54 th month, get 15y / x =1
 at 55 th month, get 15y / x =1
 at 56 th month, get 15y / x =1
 at 57 th month, get 15y / x =1
 at 58 th month, get 15y / x =1
 at 59 th month, get 15y / x =1
 at 60 th month, get 15y / x =1
 at 61 th month, get 15y / x =1
 at 62 th month, get 15y / x =1
 at 63 th month, get 15y / x =1
 at 64 th month, get 15y / x =1
 at 65 th month, get 15y / x =1
 at 66 th month, get 15y / x =1
 at 67 th month, get 15y / x =1
 at 68 th month, get 15y / x =1
 at 69 th month, get 15y / x =1
 at 70 th month, get 15y / x =1
 at 71 th month, get 15y / x =1
 at 72 th month, get 15y / x =1
 at 73 th month, get 15y / x =1
 at 74 th month, get 15y / x =1
 at 75 th month, get 15y / x =1
 at 76 th month, get 15y / x =1
 at 77 th month, get 15y / x =1
 at 78 th month, get 15y / x =1
 at 79 th month, get 15y / x =1
 at 80 th month, get 15y / x =1
 at 81 th month, get 15y / x =1
 at 82 th month, get 15y / x =1
 at 83 th month, get 15y / x =1
 at 84 th month, get 15y / x =1
 at 85 th month, get 15y / x =1
 at 86 th month, get 15y / x =1
 at 87 th month, get 15y / x =1
 at 88 th month, get 15y / x =1
 at 89 th month, get 15y / x =1
 at 90 th month, get 15y / x =1
 at 91 th month, get 15y / x =1
 at 92 th month, get 15y / x =1
 at 93 th month, get 15y / x =1
 at 94 th month, get 15y / x =1
 at 95 th month, get 15y / x =1
 at 96 th month, get 15y / x =1
 at 97 th month, get 15y / x =1
 at 98 th month, get 15y / x =1
 at 99 th month, get 15y / x =1
0
 at 0 th month, get 4y / x =4
 at 1 th month, get 1y / x =4
 at 2 th month, get 8y / x =3
 at 3 th month, get 6y / x =3
 at 4 th month, get 4y / x =3
 at 5 th month, get 2y / x =3
 at 6 th month, get 0y / x =3
 at 7 th month, get 13y / x =2
 at 8 th month, get 12y / x =2
 at 9 th month, get 11y / x =2
 at 10 th month, get 10y / x =2
 at 11 th month, get 9y / x =2
 at 12 th month, get 8y / x =2
 at 13 th month, get 7y / x =2
 at 14 th month, get 6y / x =2
 at 15 th month, get 5y / x =2
 at 16 th month, get 4y / x =2
0
*/
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}