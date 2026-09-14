#include <bits/stdc++.h>
using namespace std;

void solve(){
    long long x, y;
    cin >> x >> y;
    long long k = 1, ans = 0;

    // //尝试先都出蓝色的。出完了应该是
    // k = 1+x;
    // ans += k * (y-1);
    // ans += (y-1)*(y-2)/2;
    // cout << "blue " << ans << endl;

    // //尝试先都出红色的。
    // ans = 0;
    // ans += (y+x-1 + x) * (y) / 2;
    // cout << "red " << ans << endl;

    //构造
    ans = 0;
    if(y >= x - 2){
        ans += (x + y - 1 + 2*x - 2) * (y - x + 2)/2;
        ans += 4 * (x - 2 + 1) * (x - 2) / 2;
       // cout << "type1 " << ans << endl;
    }
    else{
        ans += 2 * ((y - 1)* 2 + x - y + x - y) * y / 2;
        //cout << "type2 " << ans << endl;
    }

    cout <<ans <<  endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}