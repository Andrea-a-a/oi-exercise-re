// 私を解決しないで。
#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__)

void solve() {
    int n;
    std::cin >> n;

    std::map<int, int> buc;
    for (int i = 1, x; i <= n; i++) {
        std::cin >> x;
        buc[x]++;
    }

    int pmex = 0;
    while (buc.count(pmex)) pmex++;

    if (!buc.count(0)) return puts("0"), void();
    if (buc[0] == 2 || buc[0] >= 4) return puts("0"), void();
    if (buc[0] == 3) {
        if (buc.count(1)) return puts("0"), void();
        buc[0] -= 2, buc[-1] += 1, buc[1] += 1;
    }

    if (!buc.count(-1)) buc[-1] = 0;

    int mex = 0;
    while (buc.count(mex)) mex++;
    for (int i = 0; i < mex; i++) {
        if (buc[i] > 1) return puts("0"), void();
    }
    int mx = mex - 1;

    for (auto it = buc.rbegin(); it != buc.rend(); it++) {
        auto jt = it;
        jt++;
        if (jt == buc.rend()) break;

        int mxd = it->second / 2;
        if (it->first - jt->first <= mxd) {
            if (jt->first == mx) return puts("0"), void();
            else jt->second += mxd - (it->first - jt->first) + 1;
        }
    }
    printf("%d\n", std::min(pmex, mex));
}

int main() {
    std::cin.sync_with_stdio(false), std::cin.tie(nullptr);

    int T = 1;
    std::cin >> T;
    while (T--) solve();
    return 0;
}