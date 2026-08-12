#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;

const long long M = 998244353;

void solve(){
    int n;
    long long x;
    cin >> n >> x;
    
    vector<i128> a(n, 0);

    for(int i = 0; i < n; i++){
        long long tmp;
        cin >> tmp;
        a[i] = tmp;
    }

    if(x == 1){
        long long ans = 0;
        for(auto i : a){
            ans = (ans + (i % M) )% M;
        }
        cout << ans << endl;
        return;
    }

    i128 opcnt = 1;
    while(opcnt > 0){
        opcnt = 0;
        for(int i = 0; i < n; i++){
            //if(a[i] == x-1) a[i] = 0;
            opcnt += a[i] / x;
            a[i] = a[i] % x;
        }
        
       // cout <<" " <<  opcnt ;
        i128 cpcnt = opcnt;
        sort(a.begin(), a.end(), greater<>());

        // cout << "before add: ";
        // for(int i = 0; i < n; i++){
        //     //cout << a[i] << " ";
        // }

        // cout << endl;
        

        for(int i = 0; i < n; i++){
            if(cpcnt > 0){
                //cout << "cpcnt: " << cpcnt << endl;
                //灌！
                if(x - a[i] <= cpcnt){
                    cpcnt -= x - a[i];
                    a[i] = x;
                    //cout << x << endl;
                    
                }
                else{
                    a[i] += cpcnt;
                    cpcnt = 0;
                    break;
                }
            }
            else{
                break;
            }
        }

        //还有剩下的
        if(cpcnt > 0){
            a[0] += cpcnt;
        }

    //     cout << "after add: ";
    //     for(int i = 0; i < n; i++){
    //         cout << a[i] << " ";
    //     }

    //    cout << "opcnt: " << opcnt << endl;

    }

    //会剩下a[0]可能>x, 然后剩下的要么=x要么<x;如果a[0]大于等于x则继续，直到剩下的都<x，所以剩下的一定<x

    //似乎还会剩下一些=x-1的
    for(int i = 0; i < n; i++){
        if(a[i] == x-1) a[i] = 0;
    }


    long long ans = 0;
    for(int i = 0; i < n; i++){
        ans = (ans + (a[i] % M) )% M;
    }
    cout << ans << endl;
    return;

}

int main(){
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}