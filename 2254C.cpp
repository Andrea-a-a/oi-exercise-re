#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> posA[2], posB[2];  // posA[0]偶链, posA[1]奇链

        // 读入字符串 a
        for (int i = 0; i < n; i++) {
            char ch;
            cin >> ch;
            if (ch == '1') {
                int chain = i % 2;      // 0 偶数链, 1 奇数链
                int idx = i / 2;        // 在该链中的位置
                posA[chain].push_back(idx);
            }
        }

        // 读入字符串 b
        for (int i = 0; i < n; i++) {
            char ch;
            cin >> ch;
            if (ch == '1') {
                int chain = i % 2;
                int idx = i / 2;
                posB[chain].push_back(idx);
            }
        }

        long long ans = 0;    // 防止溢出，用 long long
        bool possible = true;

        for (int chain = 0; chain <= 1; chain++) {
            if (posA[chain].size() != posB[chain].size()) {
                possible = false;
                break;
            }
            for (size_t k = 0; k < posA[chain].size(); k++) {
                ans += abs(posA[chain][k] - posB[chain][k]);
            }
        }

        if (!possible) {
            cout << -1 << endl;   // 不可转换，输出 -1（可根据题意调整）
        } else {
            cout << ans << endl;  // 最小操作次数
        }
    }
    return 0;
}