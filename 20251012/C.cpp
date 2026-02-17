#include <bits/stdc++.h>
using namespace std;

int t;
int a[1000020];
int maxl[1000020];
int maxr[1000020];
//long long mul[1000020];

int main(){
    ios::sync_with_stdio(0);
    cin >> t;
    for(int i = 0; i < t; i++){
        memset(a, 0, sizeof(a));
        memset(maxl, 0, sizeof(maxl));
        memset(maxr, 0, sizeof(maxr));

        //input
        int n, q;
        cin >> n;

        int temp = 0;
        for(int o = 1; o <= n; o++){
            cin >> a[o];
            temp = max(temp, a[o]);
            maxl[o] = temp;
            //cout << "maxl[" << o << "] = " << maxl[o] << endl;
        }
        temp = 0;
        for(int o = n; o > 0; o--){
            temp = max(temp, a[o]);
            maxr[o] = temp;
           // cout << "maxr[" << o << "] = " << maxr[o] << endl;
        }

        //modify
        cin >> q;
        for(int o = 0; o < q; o++){
            long long xi, vi;
            cin >> xi >> vi;
            a[xi] = a[xi] + vi;
            for(int v = 1; v <= xi; v++){
                maxr[v] = max(maxr[v], a[xi]);
            }
            //int v = n;
            for(int v = n; v >= xi; v--){
                maxl[v] = max(maxl[v], a[xi]);
            }
            long long ans = 0;
            for(int v = 1; v <= n; v++){
                ans += min(maxl[v], maxr[v]) - a[v];
            }
            //cout << "                       " << ans << endl;
            cout << ans << endl;
        }
    }



    return 0;
}