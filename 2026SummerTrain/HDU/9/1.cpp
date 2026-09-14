#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin >> n;
    long long ans = 0;
    vector<long long> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        ans += a[i];
    }

    sort(a.begin(), a.end(), greater<long long>());

    ans += a[0];
    cout << ans << endl;
}


int main(){

    ios::sync_with_stdio(false); cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}