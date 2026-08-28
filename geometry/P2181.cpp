#include <bits/stdc++.h>
using namespace std;
int main(){
    unsigned long long n;
    cin >> n;
    unsigned long long ans = 0;
    for(unsigned long long i = 1; i <= n-2; i++){
        ans += (i-1) * (n-i) * (n-1-i) / 2;
    }

    cout << ans;
}