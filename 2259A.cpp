#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n, k;
    cin >> n >> k;
    int ans = 0;
    for(int i = 0; i < n/k; i++){
        bool havezero = 0;
        for(int o = 0; o < k; o++){
            char x;
            cin >> x;
            if(x == '0')  havezero = 1;
        }
        if(!havezero)   ans++;
    }    
    cout << ans << endl;
}

int main(){
    int n;
    cin >> n;
    while(n--){
        solve();
    }
    return 0;
}