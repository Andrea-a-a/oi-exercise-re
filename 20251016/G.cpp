#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//#define long long long long;
const long long N = 1e9;
const long long M = 0;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long t,n,m,k;
    cin >> t >> n >> m >> k;

    vector<pair<long long, long long>> tx(m);
    for (long long i = 0; i < m; ++i) {
        cin >> tx[i].first >> tx[i].second;
    }

    sort(tx.begin(), tx.end());
    long long time = 1,maxcnt = 0,mincnt = 0,idx = 0;
    while(time <= t){
        if(tx[idx].first == time){
            maxcnt += tx[idx].second;
            mincnt += tx[idx].second;
            idx++;
        }
        if(time == t){
            if(n != mincnt){
                cout << "Wrong Record" << "\n";
                return 0;
            }
        }
        mincnt = max(M,mincnt-k);
        time++;
    }
    long long ans = N,index = -1;
 
    // 特判醒来那一次能不能排队
    if(tx[idx-1].first == t){
        if((n+1) % k == 0) ans = (n+1)/k;
        else ans = (n+1)/k +1;
        index = t;
    }
    n = max(M,n-k);   
    while(time <= tx[m-1].first){
        if(tx[idx].first == time)
            n += tx[idx].second;
            idx++;
        long long temp = 0;
        if((n+1) % k == 0)  temp = (n+1)/k;
        else temp = (n+1)/k +1;
        if(temp <= ans){
            ans = temp;
            index = time;
        }
        n = max(M,n-k); 
        time++;
    }
    cout << index << " " << ans << "\n";
    return 0;
}