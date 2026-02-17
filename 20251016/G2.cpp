#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 1e9;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t,n,m,k;
    cin >> t >> n >> m >> k;

    vector<pair<int, int>> tx(m);
    for (int i = 0; i < m; ++i) {
        cin >> tx[i].first >> tx[i].second;
    }

    sort(tx.begin(), tx.end());
    int time = 1,maxcnt = 0,mincnt = 0,idx = 0;
    while(time <= t){
        if(tx[idx].first == time){
            maxcnt += tx[idx].second;
            mincnt += tx[idx].second;
            idx++;
        }
        if(time == t){
            if(n < mincnt || n > maxcnt){
                cout << "Wrong Record" << "\n";
                return 0;
            }
        }
        mincnt = max(0,mincnt-k);
        time++;
    }
    int ans = N,index = -1;

    // 特判醒来那一次能不能排队
    if(tx[idx-1].first == t){
        ans = (n+k)/k;
        index = t;
    }
    n = max(0,n-k);   
    while(time <= tx[m-1].first){
        if(tx[idx].first == time)
            n += tx[idx].second;
            idx++;
        if( (n+1)/k <= ans){
            ans = (n+k)/k;
            index = time;
        }
        n = max(0,n-k); 
        time++;
    }
    cout << index << " " << ans << "\n";
    return 0;
}