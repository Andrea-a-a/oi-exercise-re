#include <bits/stdc++.h>
using namespace std; 

#define int long long

void solve(){
    int n;
    cin >> n;
    int sum = 0;
    vector<int> fa(n+1), a(n+1, 0), b(n+1, 0);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        sum += a[i];
    }
    fa[1] = 1;
    for(int i = 2; i <= n; i++){
        cin >> fa[i];
    }

    // int time = 10;
    // while(time--){
        for(int i = 2; i <= n; i++){
            b[fa[i]] += a[i] + b[i];
            b[i] = 0;
        }
    //     cout << b[1] << endl;
    // }


    // cout << "  " << sum - a[1] << endl;

    if(sum - a[1] == 0){
        for(int i = 2; i <= n; i++){
            b[fa[i]] += a[i] + b[i];
            b[i] = 0;
        }
        if(b[1] == 0){
            cout << "0" << endl;
        }
        else if(b[1] > 0){
            cout << "1" << endl;
        }
        else{
            cout << "-1" << endl;
        }

    }
    else if(sum - a[1] > 0){
        cout << "1" << endl;
    }
    else{
        cout << "-1" << endl;
    }
        


}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}