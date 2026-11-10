// 枚举元组
// 子集枚举
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
int n, m;
vector<int> w;

void dfs(int i) {
    //cout << "dfsing: " << i << " " << k << endl;
    if (i == m) {
        //if (k != m) return;
        // cout << "k: "  << k << endl;
        for (auto u : w) {
            cout << u  << " ";
        }
        cout << endl;
        return;
    }

    for(int z = 1; z <= n; z++){
        w.push_back(z);
        dfs(i + 1);
        w.pop_back();
    }


    // dfs(i + 1, k);
}

int main() {

    cin >> m >> n;

    dfs(0);
}