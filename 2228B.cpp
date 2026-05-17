#include <iostream>
#include <math.h>
using namespace std;

#define int long long

signed main(){
    int t;
    cin >> t;
    while(t--){
        int n, x, y, k;
        cin >> n >> x >> y >> k;
        if(n <= 3){
            cout << 1 << endl;
        }
        // else if(n % 2 == 0 && abs(x-y) == n/2){
        //     // if(n == 4){
        //     //     cout << 1 << endl;
        //     // }
        //     // else{
        //         cout << k + n/2 - 1 << endl;
        //     //}
        // }
        else{
            cout << k + min(abs(x-y), n-abs(x-y)) << endl;
        }
    }





    return 0;
}