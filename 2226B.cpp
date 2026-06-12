#include <iostream>
using namespace std;

int gcd(int a, int b){
    if(b == 0){
        return a;
    }

    return gcd(b, a%b);
}

int t;

int main(){

    cin >> t;
    while(t--){

        int n;
        int first;
        int ans = 0;
        cin >> n >> first;
        for(int i = 1; i < n; i++){
            int last;
            cin >> last;
            if(gcd(last, first) == abs(last - first)){
                ans++;
            }

            first = last;
        }
        cout << ans << endl;

    }


    return 0;
}