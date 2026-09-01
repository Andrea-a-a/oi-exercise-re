// 树状数组 1
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

    vector<long long> c(n+1, 0);
    for (int i = 1; i <= n; i++) {
        long long tmp;
        cin >> tmp;
        plu(i, tmp, c, n);
    }

    while (m--) {
        long long opt, w, e;
        cin >> opt >> w >> e;
        if (opt == 1) {
            plu(w, e, c, n);
        } else {
            cout << query(e, c) - query(w-1, c) << '\n';
        }
    }
}