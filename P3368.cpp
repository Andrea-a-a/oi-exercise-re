// 树状数组 2
#include <iostream>
#include <vector>

using namespace std;

int lowbit(int x) {
    return ((-x) & x);
}

void plu(int i, long long k, vector<long long> &a, int n) {
    while (i <= n) {
        a[i] += k;
        i = i + lowbit(i);
    }
}

// 求出[1, i]的和
long long query(int i, vector<long long> &a) {
    long long ans = 0;
    while (i > 0) {
        ans += a[i];
        i = i - lowbit(i);
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;

    // int t;
    // while(cin >> t){
    //     cout << lowbit(t) << endl;
    // }

    vector<long long> c(n + 1, 0);

    long long c1;
    cin >> c1;
    plu(1, c1, c, n);
    long long tmp;
    for (int i = 2; i <= n; i++) {
        cin >> tmp;
        plu(i, tmp - c1, c, n);
        c1 = tmp;
    }
    while (m--) {
        long long opt;
        cin >> opt;
        if (opt == 1) {
            int x, y;
            long long k;
            cin >> x >> y >> k;
            plu(x, k, c, n);
            plu(y + 1, -k, c, n);

        } else {
            int x;
            cin >> x;

            cout << query(x, c) << '\n';
        }

    }
}