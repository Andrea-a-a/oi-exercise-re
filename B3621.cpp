// 枚举元组
// 子集枚举
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
int n, m;
vector<int> w;

void dfs(int i, int k) {
    if (i == n) {
        if (k != m) return;
        // cout << "k: "  << k << endl;
        for (auto u : w) {
            cout << setw(3) << u + 1;
        }
        cout << endl;
        return;
    }
    w.push_back(i);
    dfs(i + 1, k + 1);
    w.pop_back();

    dfs(i + 1, k);
}

int main() {

    cin >> n >> m;

    dfs(0, 0);
}