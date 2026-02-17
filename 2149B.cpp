#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int t;


int main(){
    cin >> t;
    for(int i = 0; i < t; i++){
        int n;
        cin >> n;
        int a[200010];

        for(int o = 0; o < n; o++){
            cin >> a[o];
        }
        sort(a,a+n);

        int ans = 0;
        for(int o = n-1; o > 0; o = o-2){
            ans = max((a[o]-a[o-1]),ans);        
        }

        //cout << '~' << ans << '~' << endl;
        cout << ans << endl;
    }



    return 0;
}