#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1e9+7;
//long long two[100100];

long long mod(long long n){
    long long ans = 1;
    long long base = 2;
    //int i = 0;
    while(n > 0){
        if(n % 2 == 1){
            ans *= base;
            ans %= MOD;
        }
        n /= 2;
        base *= base;
        base %= MOD;

    }
    return ans;
}



void solve(){
    int n, cntdist = 0, cntminus = 0, cntpair = 0;
    cin >> n;

    vector<long long> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] == -1){
            cntminus++;
        }

        if(cntdist == 0){
            cntdist++;
        }
        else{
            if(a[i] != a[i-1]){
                cntdist++;
                if(a[i] == a[i-1] + 1){
                    cntpair++;
                }
            }
        }
    }

    //cout << cntminus << " " << cntdist << " " << cntpair << endl;

    unsigned long long ans = 0;
    ans = mod(n-cntdist);
    
    if(cntminus > 0){
        ans *= cntpair + 1;
    }
    ans %= MOD;
    cout << ans << endl;

}

int main(){

    // int x = 2e5+10;
    // two[0] = 1;
    // int cnt = 1;
    // while(x > 0){
    //     two[cnt] = two[cnt-1] * 2;
    //     two[cnt] %= MOD;
    //     x = x >> 1;
    //     cnt++;
    //     //cout << two[cnt-1] << endl;
    // }

    int t;
    cin >> t;
    while(t--){
        solve();
        // int n;
        // cin >> n;
        //cout << mod(14);
    }



    return 0;
}