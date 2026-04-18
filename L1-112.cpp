#include <iostream>
using namespace std;

#define ll long long

ll n, m, k, a[1020][1020];
bool isBoomedl[1020], isBoomedr[1020];


int main(){
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++){
        for(int o = 1; o <= m; o++){
            cin >> a[i][o];
        }
    }

    for(int i = 1; i <= k; i++){
        //step1 find max
        int l = 1, r = 1, max = -1073741824;
        for(int w = 1; w <= n; w++){
            for(int q = 1; q <= m; q++){
                if(a[w][q] >= max && !isBoomedl[w] && !isBoomedr[q]){
                    max = a[w][q];
                    l = w;
                    r = q;
                }
            }
        }
        //step2 boom
        isBoomedl[l] = 1;
        isBoomedr[r] = 1;


    }

    /*
    int cnt1 = 0, cnt2 = 0;
    for(int i = 1; i <= n; i++){
        cnt2 = 0;
        if(cnt1 == 0){
            for(int o = 1; o <= m; o++){
                if(!isBoomed[i][o]){
                    if(cnt2 == 0){
                        cout << a[i][o];
                        cnt2++;
                    }
                    else{
                        cout << " " << a[i][o];
                    }
                }
            }
            cnt1++;
        }
        else{
            if(!isBoomed[i][1])cout << endl;
            for(int o = 1; o <= m; o++){
                if(!isBoomed[i][o]){
                    if(cnt2 == 0){
                        cout << a[i][o];
                        cnt2++;
                    }
                    else{
                        cout << " " << a[i][o];
                    }
                }
            }
        }
    }
    */

    //int cnt1 = 0;
    for(int i = 1; i <= n; i++){
        int cnt2 = 0;
        if(isBoomedl[i])    continue;
        
            for(int o = 1; o <= m; o++){
                if(isBoomedr[o])    continue;
                else{
                    if(cnt2 == 0){
                        cout << a[i][o];
                        cnt2++;
                    }
                    else{
                        cout << " " << a[i][o];
                    }

                }
            }
        cout << endl;
    }

    return 0;


}
