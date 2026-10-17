#include <bits/stdc++.h>
using namespace std;

int main(){
    long long l = 0, r = 1e9+1;

    while (l < r) {
        int mid = (l + r) / 2;
        cout << "? " << mid << endl;
        int s;
        cin >> s;
        if (s == 1) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << "! " << l;

    
}