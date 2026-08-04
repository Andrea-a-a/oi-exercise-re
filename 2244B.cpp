#include <iostream>
using namespace std;

bool solve(){
    int n;
    cin >> n;
    long long left = 0;
    bool ok = 1;
    for(int i = 1; i <= n; i++){
        long long ai;
        cin >> ai;

        
            left += ai - i;
        

        if(left < 0){
            ok = false;
        }

    }
    //ok = true;
    return ok;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        solve() ? cout << "YES" << endl : cout << "NO" << endl;
    }


    return 0;
}