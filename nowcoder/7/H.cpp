#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    if(n == 1){
        cout << "3 1 2" << endl;
    }
    else if(n == 2){
        cout << "4 0 1" << endl << "5 2 3" << endl;
    }
    else if(n % 2 == 1){
        cout << 3*n-1 << " 0 " << (3 * n - 1) / 2 << endl;
        for(int i = 1; i <= n-1; i++){
            if(i % 2 == 0){
                cout << (3 * n - 1 + i) / 2 << " " << i << " " << (3 * n - 1 - i) / 2 << endl;
            }
        }
        int l = 2 * n, r = 3 * n - 2;
        for(int i = 0; i < n / 2; i++){
            cout << r  << " " << r - l << " " << l << endl;
            l += 1;
            r -= 1;
        }
    }
}