#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin >> n;

    vector<int> cnt(n+20, 0);




    for(int i = 0; i < n; i++){
        long long tmp;
        cin >> tmp;
        if(tmp >= n+20) continue;
        else{
            cnt[tmp]++;
        }
    }

    int mex = n;
    for(int i = 0; i <= n-1; i++){
        if(cnt[i] == 0){
            mex = min(mex, i);
            break;
        }
    }

    // for(int i = 0; i <= n-1; i++){
    //     cout << "cnt[ " << i << "] = " << cnt[i]<< endl;
    // }

   

    if(cnt[0] != 1 && cnt[0] != 3) {
        cout << "0" << endl;
        return;
    }

    if(cnt[0] == 3){
        cnt[1]++;
        cnt[0] = 1;
    }

    //cout << "ori mex = " << mex << endl;

    for(int i = n+19; i >= 1; i--){
        if(cnt[i] >= 2){
            cnt[i-1] += cnt[i] / 2;
            cnt[i] = cnt[i] % 2;
        }
    }

    


    if(cnt[0] %2 == 0){
        cout << '0' << endl;
        return;
    }

    //寻找mex
  
    for(int i = 0; i <= n-1; i++){
        if(cnt[i] == 0){
            mex = min(i, mex);
            break;
        }
    }

    cout << mex << endl;
    return;





}


int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}