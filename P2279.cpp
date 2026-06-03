#include <iostream>
using namespace std;

int n, m;
const int MAXN = 1e6+10;
long long a[MAXN];


int main() {

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    while(m--) {
        long long q;
        cin >> q;
        long long ans = lower_bound(a, a+n, q) - a;
        if(a[ans] != q) {
            cout << "-1 ";
        }
        else {
            cout << ans + 1 << ' ';
        }
    }


    return 0;
}