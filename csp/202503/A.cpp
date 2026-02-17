#include <bits/stdc++.h>
using namespace std;

long long b, c, l, r;

int main(){
    cin >> b >> c >> l >> r;
    long long ans = 0;
    for(int i = l; i <= r; i++){
        if(i % 2 == 0){
            ans += i * i + b * i + c;
        }
    }
    cout << ans * 2;
}