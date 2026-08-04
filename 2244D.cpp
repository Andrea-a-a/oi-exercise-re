#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

void solve(){
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    vector<long long> sum;
    vector<int> b(m);

    for(int i = 0; i < n; i++){
        ///cout << "meow";
        cin >> a[i];
        if(i == 0){
            sum.push_back(a[i]);
        }
        else{
            sum.push_back(sum[i-1] + a[i]);
        }
        //cout << "sum:" << sum[i] << endl;
    }

    for(int i = 0; i < m; i++){
        //cout << " i:" << i << endl;
        cin >> b[i];
        b[i]--;
    }

    sort(b.begin(), b.end());

    //cout << sum[4] << endl;
    //cout << b[2];
    //cout << "maxb:" << b[m-1] << endl;
    
    long long ans = 0;
    ans += sum[n-1] - sum[b[m-1]];


    for(int i = m-2; i >= 0; i--){
        ans += abs(sum[b[i+1]] - sum[b[i]]);
    }

    ans += abs(sum[b[0]]);

    cout << ans << endl;
}

int main(){

    int t;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;



}
