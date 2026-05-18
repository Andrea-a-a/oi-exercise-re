#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

void inni();

int t;
const int MAXN = 1e5+10;
long long ai[MAXN], bi[MAXN], ci[MAXN];
long long di;
long long sum;
int cnt[MAXN];

int main(){
    ios::sync_with_stdio(0);
    cin >> t;
    for(int i = 0; i < t; i++){
        inni();
        int n;
        unsigned long long x;
        cin >> n >> x;
        for(int i = 1; i <= n; i++){
            cin >> ai[i] >> bi[i] >> ci[i];
            di = max(di, ai[i] * bi[i] - ci[i]);
            sum += ai[i] * (bi[i] - 1);
        }

        //首先，在回滚前的次数
        if(x <= sum){
            cout << "0" << endl;
            continue;
        }
        else{
            // bool isOK = 0;
            // //int sum2 = 0;
            // for(int i = 1; i <= n; i++){
            //     if(di[i] > 0){
            //         isOK = 1;
            //     }
            // }
            // if(!isOK){
            //     cout << "-1" << endl;
            //     continue;
            // }

            if(di <= 0){
                cout << "-1" << endl;
                continue;
            }

        }

        //sort(di+1, di+n+1);
        int sumtmp = 0, cnt = 0;
        // for(int i = n; ; i = ((i-2)+n)%n + 1){
        //     sumtmp += di[i];
        //     cnt++;
        //     if(sumtmp >= x - sum){
        //         cout << cnt << endl;
        //         break;
        //     }
        // }

        
        // for(int i = 1; i <= n; i++){
        //     cout << "di[ " << i << " ] = " << di[i] << endl;
        // }

        if((x-sum) % di == 0){
            cout << (x-sum)/di << endl;
        }
        else{
            cout << (x-sum) / di+1 << endl;
        }

    }
    
    return 0;
}

void inni(){
    memset(ai, 0, sizeof(ai));
    memset(bi, 0, sizeof(bi));
    memset(ci, 0, sizeof(ci));
    memset(cnt, 0, sizeof(cnt));
    //memset(di, 0, sizeof(di));
    di = 0;
    sum = 0;
}

