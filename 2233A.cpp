#include <iostream>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n, x, y, z;
        cin >> n >> x >> y >> z;

        int ans1 = n/(x+y);
        if(n%(x+y) != 0)    ans1++;

        if((x+y) * z >= n){
            cout << ans1 << endl;
            continue;
        }
        else{
            int ans2 = (n-x*z)/(x+10*y) + z;
            if((n-x*z) % (x+10*y) != 0) ans2++;
            cout << min(ans1, ans2) << endl;
        }


    }

    return 0;
}