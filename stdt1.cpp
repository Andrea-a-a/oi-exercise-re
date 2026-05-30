#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
        freopen("input.txt","r",stdin);
    freopen("expected.txt","w",stdout);
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> ice, fire;
    for (int i = 0; i < n; i++) {
        int type, a;
        cin >> type >> a;
        if (type == 0) ice.push_back(a);
        else fire.push_back(a);
    }

    sort(ice.rbegin(), ice.rend());
    sort(fire.rbegin(), fire.rend());

    double total = 0;
    int enemy_ice = m;
    int enemy_fire = n - m;

    // 火打冰 (2x)
    for (int i = 0; i < fire.size(); i++) {
        if (enemy_ice > 0) {
            total += fire[i] * 2.0;
            enemy_ice--;
        } else {
            total += fire[i] * 1.0;
        }
    }

    // 冰打火 (1.5x)
    for (int i = 0; i < ice.size(); i++) {
        if (enemy_fire > 0) {
            total += ice[i] * 1.5;
            enemy_fire--;
        } else {
            total += ice[i] * 1.0;
        }
    }

    printf("%.0f\n", total); // A_i均为10的倍数，结果必为整数[span_6](end_span)
    return 0;
}