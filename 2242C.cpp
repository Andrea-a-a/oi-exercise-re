#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve(){
    int ans = 0;
    int n, k;
    cin >> n >> k;

    vector<int> a;
    vector<int> sum;
    int tmp, cnt = 0;
    cin >> tmp;

    a.push_back(tmp);
    sum.push_back(1);

    for(int i = 1; i < n; i++){
        cin >> tmp;
        a.push_back(tmp);
        if(a[i] != a[i-1]){
            cnt++;
            sum.push_back(1);
        }
        else{
            sum[cnt]++;
        }
    }

    sort(sum.begin(), sum.end(), greater<>());
    int indexr = cnt;


    while(sum[0] > 0){
        
        // for(int i = 0; i <= indexr; i++){
        //     cout << sum[i] << " ";
        // }

        // cout << "n: " << n << endl;
        
        //检查现在
        if(sum[indexr] > 1){
            for(int i = 0; i <= indexr; i++){
                sum[i]--;
            }
            n -= indexr + 1;
        }
        else{
            if(k - n >= 0 && (k - n) % (indexr+1) == 0){
                ans++;
            }

            for(int i = 0; i <= indexr; i++){
                sum[i]--;
            }
            n -= indexr + 1;
            while(sum[indexr] == 0 && indexr > 0){
                indexr--;
                //cnt = indexr;
            }
        }
        
    }



    cout << ans << endl;


}

int main(){

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    



    return 0;
}