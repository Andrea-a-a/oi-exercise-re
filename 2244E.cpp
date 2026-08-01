//2244E
#include <iostream>
#include <vector>
using namespace std;

void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> presum(n+1, 0);
    vector<bool> indic(n+1);
    for(int i = 1; i <= n; i++){
        char tmp;
        cin >> tmp;
        if(tmp != i%2 + '0'){
            indic[i] = false;
        }
        else{
            indic[i] = true;
        }
    }
    presum[1] = 1;
    for(int i = 2; i <= n; i++){
        if(indic[i] == indic[i-1]){
            presum[i] = presum[i-1];
        }
        else{
            presum[i] = presum[i-1] + 1;
        }
    }

    while(m--){
        int l, r, k;
        int ans = 0;
        cin >> l >> r >> k;
        ans = presum[r] - presum[l-1];
        if(presum[l-1] == presum[l]){
            ans++;
        }
        ans = ans/2;
        if(ans > k){
            cout << "NO" << endl;
        }
        else{
            cout << "YES" << endl;
        }
    }

}

int main(){

    int t;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}