#include <iostream>
using namespace std;

int main(){

    int t;
    cin >> t;
    while(t--){
        int mi = 10;
        int mx = -1;
        int n;
        cin >> n;
        while(n--){
            int tmp;
            cin >> tmp;
            mi = min(tmp, mi);
            mx = max(tmp, mx);
        }
        cout << mx - mi + 1 << endl;
    }




    return 0;
}