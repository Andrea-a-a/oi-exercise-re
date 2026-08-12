#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    
    long long m;
    cin >> n >> m;
    vector<long long> a(2*n+1, 0);
    for(int i = 1; i <= n; i++){
        cin >> a[2 * i - 1] >> a[2 * i];
    }
    
    int ans1 = 0;
    long long b1 = a[1] + m;
    if(a[2] > b1) ans1++;
    for(int i = 2; i <= n; i++){
        int l = 2*i-1, r = 2*i;
        if(a[2 * i - 1] > a[2 * i]) swap(a[2*i-1], a[2*i]);
        if(b1 < a[l]) ans1 += 2;
        else if(b1 < a[l] || b1 < a[r]) {
            ans1 += 1;
        } 
        else {
            long long t= b1 - a[l] + b1 - a[r];
            if(t < m)  ans1 += 1;
        }

    }


    int ans2 = 0;
    if(a[2] + m > a[1]) ans2++;
    for(int i = 2; i <= n; i++){
        int l = 2*i-1, r = 2*i;
        long long d1= max(0LL, a[1] - a[l]);
        long long d2= max(0LL, a[1] - a[r]);


            if (d1 == 0 && d2 == 0) {
                ans2 += 2;
            } else if (d1 == 0 || d2 == 0) {
                long long d_other = max(d1, d2);
                if (m > d_other) ans2 += 2;      
                else ans2 += 1;                 
            } else {
                if (m > d1 + d2) ans2 += 2;    
                else if (m > d1 || m > d2) ans2 += 1; 
                
            }
    }

    cout << ans1 << " " << ans2 << endl;

}

int main(){
    ios::sync_with_stdio(0); cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;


}