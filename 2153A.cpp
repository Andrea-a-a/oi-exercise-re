#include <bits/stdc++.h>
using namespace std;
int t;
int b[110];

int main(){
    cin >> t;
    for(int i = 0; i < t; i++){
        int n;
        cin >> n;
        memset(b, -1, sizeof(b));
        for(int o = 1; o <= n; o++){
            cin >> b[o];
        }
        sort(b+1, b+n+1);
        int ans = unique(b+1, b+n+1) - (b+1);
       // cout << '`' <<  ans << '`' << endl
       cout << ans << endl;
    }
    return 0;
}