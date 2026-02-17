//字符串hash
#include <bits/stdc++.h>
using namespace std;

long long n;
long long hsh[10010];
const int mol = 998244353;
const int base = 10003;


int main(){

    cin >> n;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int o = 0; o < s.length(); o++){
            hsh[i] = (s[o] + hsh[i] * base) % mol;
        }
    }
    sort(hsh, hsh + n);
    cout << unique(hsh, hsh+n) - hsh;

    return 0;
}