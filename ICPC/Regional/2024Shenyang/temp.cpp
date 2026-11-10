#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 5e5 + 5;
vector<int> A;
vector<int> B;

bool nixudui(vector<int> &A) {
}

void solve() {
    int n;
    cin >> n;
    int mvp;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }
    bool TA = nixudui(A);
    bool TB = nixudui(B);
    if (TA == TB) {
        mvp = 1; // B wins
    } else {
        mvp = 0;
    }
}

struct BIT {
    int n;
    vector<int> w, chk;
    BIT(auto &in) : n(in.size() - 1), w(in.size()), chk(in) {}
    void add(int x, long long v) {
        for (; x <= n; x += x & -x) {
            w[x] += v;
        }
    }
    long long rangeAsk(int l, int r) {
        auto ask = [&](int x) {
            long long ans = 0;
            for (; x; x -= x & -x) {
                ans += w[x];
            }
            return ans;
        };
        return ask(r) - ask(l - 1);
    }
    long long get() {
        vector<array<int, 2>> alls;
        for (int i = 1; i <= n; i++) {
            // array<int, 2> qwe( = {chk[i], i});
            alls.push_back({chk[i], i});
        }
        sort(alls.begin(), alls.end());
        long long ans = 0;
        for (auto [val, idx] : alls) {
            ans += rangeAsk(idx + 1, n);
            add(idx, 1);
        }
        return ans;
    }
};

int main() {
    A.push_back(1);
    A.push_back(5);
    A.push_back(3);
    A.push_back(2);
    BIT Bit(A);
    cout << Bit.get() << endl;
    int TIME;
    cin >> TIME;
    // TIME = 1;
    while (TIME--) {
        solve();
    }
    return 0;
}