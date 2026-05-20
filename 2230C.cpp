#include <iostream>
#include <cstring>
using namespace std;

int t;
const long long MAXN = 2e5+10;
unsigned long long c[MAXN];

int main(){
    cin >> t;
    while(t--){
        long long n;
        cin >> n;

        memset(c, 0, sizeof(c));

        unsigned long long ans = 0;
        long long cntfor1 = 0, cnt1 = 0;
        //bool have2 = 0;
        long long sum = 0;

        for(int i = 1; i <= n; i++){
            cin >> c[i];
            sum += c[i];
            if(c[i] >= 2){
                //have2 = 1;
                ans+=c[i];
            }
            
            if(c[i] == 1){
                cnt1++;
            }

            if(c[i] >= 4){
                
                cntfor1 += c[i]/2-1;
            }


        }

        if(sum < 3){
            cout << "0" << endl;
            continue;
        }

        // if(have2){
        //     cntfor1++;
        // }
        if(c[n] >= 2 && n >= 2 && c[n-1] == 1){
            cntfor1++;
        }
        
        
        cout << ans + min(cntfor1, cnt1) << endl;


    }

    return 0;

}