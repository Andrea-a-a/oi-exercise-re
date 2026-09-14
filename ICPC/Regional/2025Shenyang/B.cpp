#include <bits/stdc++.h>
using namespace std;

void solve() {

    int n, m, a, b;
    cin >> n >> m >> a >> b;
    map<int, int> cnt;
    int totcnt = 0;
    for (int i = 0; i < n; i++) {
        for (int o = 0; o < m; o++) {
            int tmp;
            cin >> tmp;
            if (tmp != 0) {
                cnt[tmp]++;
                totcnt++;
            }
        }
    }
    vector<int> cntsort;
    for (auto i : cnt) {
        cntsort.push_back(i.second);
    }
    sort(cntsort.begin(), cntsort.end(), greater<>());

    // 枚举
    int totcol = cntsort.size();

    vector<long long> pre1(totcol), pre2(totcol);
    pre1[0] = cntsort[0];
    pre2[0] = cntsort[0];

    for (int i = 1; i < totcol; i++) {
        // cerr<< "   " << cntsort[i] << " " ;
        pre1[i] = pre1[i - 1] + cntsort[i];
        pre2[i] = pre2[i - 1] + pre1[i];
    }
    // cerr<< totcnt <<"  " << totcol << endl;
    // for(auto i : cntsort)  cerr<< "   " << i << " " ;
    // cerr << endl;

    // for(auto i : pre1)  cerr<< "   " << i << " " ;
    // cerr << endl;

    // for(auto i : pre2)  cerr<< "   " << i << " " ;
    // cerr << endl;

    long long totans = totcnt * a;
    // cerr << totans << "    ";
    for (int i = 1; i <= totcol; i++) {
        // 对于[0,i)使用橡皮擦，对于剩下的使用画笔
        long long ans = 0;
        ans = (n * m - totcnt) * (i);
        if (i > 1) {
            ans += pre2[i - 2];
        }
        ans *= b;

        /*
         *  nm - totcnt // i = 1
         *  nm - totcnt + a[0] // pre2[0] // i = 2
         *  nm - totcnt + a[0] + a[1] // pre2[1]
         *
         * [0, i) 一共有i项
         * 是否可以算出前缀和的前缀和
         *
         *
         *
         */
        // 还剩下[i, totcol-1]
        if (i - 1 >= 0) ans += a * (totcnt - pre1[i - 1]);
        cerr << " i = " << i << " ans = " << ans << endl;
        totans = min(ans, totans);
    }

    cout << totans << endl;
}

int main() {

    // 观察
    // 假设在n*m里有k个格子有颜色
    // 如果在只有画笔工具的时候，其代价为a*k
    // 如果在只有橡皮擦的时候，代价为b * sum( (nm - 除了这个图层的颜色还剩下多少))
    // 对于一个颜色，只需要选择一种放入方式，因为显然两种都用是不划算的
    // 如何在只有橡皮擦的时候确定图层顺序？
    // 是否应该先尽可能用橡皮擦，然后对剩下的用画笔？
    // sort是nmlognm，枚举颜色应该是nm
    // 是否具有二分的特性？

    // 样例3：先铺一层2，再铺一层4，再点掉4的两个点，再画一个1
    // HOW？？？？？？

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}