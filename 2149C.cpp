#include <iostream>
//#include <bits/stdc++.h>
using namespace std;

int t;

int main(){

    cin >> t;

    for(int i = 0; i < t; i++){
        int n, k;
        cin >> n >> k;

        int a[200020];
        int tong[200020]{};

        for(int o = 0; o < n; o++){
            cin >> a[o];
            tong[a[o]]++;
        }

        int ans = 0;
        if(k == 0)  {ans = tong[0]; cout << ans << endl;}
        else {
            int change = k;
            for(int o = 0; o < k; o++){
                if(tong[o] > 0) change--;
            }
            if(change < tong[k])    change = tong[k];
            //cout << '@'<<change << endl;
            cout << change << endl;
        }


    }
    return 0;
}