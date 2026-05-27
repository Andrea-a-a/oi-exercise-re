#include <iostream>
#include <cstring>
using namespace std;

int t;
const int MAXN = 5e5+10;
int n, a[MAXN], b[MAXN], laa[MAXN], lab[MAXN], dp[MAXN];


int main(){
    ios::sync_with_stdio(0);
    cin >> t;
    while(t--){


        cin >> n;

        for(int i=0;i<=n+2;i++){
            laa[i]=n+1;
            lab[i]=n+1;
            dp[i]=n;
            a[i] = 0;
            b[i] = 0;
        }

        for(int i = 1; i <= n; i++){
            cin >> a[i];
        }
        for(int i = 1; i <= n; i++){
            cin >> b[i];
        }

        long long ans = 0;

        //从后向前dp
        for(int i = n; i >= 1; i--){
            //维护当前的最近

            laa[a[i]] = i;

            lab[b[i]] = i;

            if(a[i] == b[i]){
                if(laa[a[i]+1] == lab[a[i]+1]){
                    dp[i] = dp[laa[a[i]+1]];
                }
                else{
                    dp[i] = min(laa[a[i]+1], lab[a[i]+1])-1;
                }
            }

            if (laa[1] != lab[1]) {
                ans += min(laa[1], lab[1]) - i;
            } else {
                ans += dp[laa[1]] - i + 1;
            }

        }
        cout << ans << endl;
    
    }

    


    return 0;
    
}