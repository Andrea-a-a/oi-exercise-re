#include <bits/stdc++.h>
using namespace std;

#define int long long

int t;

signed main(){

    cin >> t;
    while(t--){

        int x, y;
        cin >> x >> y;
        //cout << x  << y << endl;
        int div = y / x;
        if(div == 2){
            cout << "NO" << endl;
            continue;
        }
        for(int i = 2; i < div; i++){
            if(y % (i * x) != 0){
                cout << "YES" << endl;
                break;
            }

            if(i == div-1){
                cout << "NO" << endl;
            }
        }


    }

    return 0;

}