#include <bits/stdc++.h>
using namespace std;

int main(){

    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n, n), b(n, n);
    while(m--){
        int x, y;
        cin >> x >> y;
        a[x-1]--;
        b[y-1]--;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    cout << min(a[0], b[0]) << endl;
    return 0;

}