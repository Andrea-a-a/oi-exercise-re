#include <bits/stdc++.h>
using namespace std;

//暴力。95分，tle。

long long a[510][510];
int n, l;

bool csp(int x, int y, int k);

int main(){
    ios::sync_with_stdio(0);
    cin >> n >> l;
    for(int i = 1; i <= n; i++){
        for(int o = 1; o <= n; o++){
            cin >> a[i][o];
        }
    }
    for(int k = 1; k <= l-1; k++){
        for(int x = 1; x <= n-9+1; x++){
            for(int y = 1; y <= n-5+1;y++){
                if(csp(x, y, k)){
                    //cout << "y:"  <<y << " k:" <<  k << endl;
                    cout << k << endl;
                    x = n-9+1;
                    break;
                }
                int ind = 0;
                for(int o = 0; o <= 5; o++){
                    if(a[y+o][x]<k) ind = o;
                }
                y = y+ind;
                
            }
        }
    }

    return 0;
}

bool csp(int y, int x, int k){
    if( a[x][y] >= k && a[x][y+1] >= k && a[x][y+2]>=k 
        && a[x][y+3] >= k && a[x][y+4]  >= k && a[x][y+5]>=k
        && a[x][y+6]>= k  && a[x][y+7]  >= k && a[x][y+8]>=k 
        && a[x+1][y] >= k && a[x+1][y+1] < k && a[x+1][y+2] < k 
        && a[x+1][y+3]>=k && a[x+1][y+4] < k && a[x+1][y+5] < k 
        && a[x+1][y+6]>=k && a[x+1][y+7] < k && a[x+1][y+8] >=k
        && a[x+2][y] >= k && a[x+2][y+1] < k && a[x+2][y+2] < k 
        && a[x+2][y+3]>=k && a[x+2][y+4]>= k && a[x+2][y+5] >=k 
        && a[x+2][y+6]>=k && a[x+2][y+7]>= k && a[x+2][y+8] < k
        && a[x+3][y] >= k && a[x+3][y+1] < k && a[x+3][y+2] < k 
        && a[x+3][y+3]< k && a[x+3][y+4] < k && a[x+3][y+5]>= k 
        && a[x+3][y+6]>=k && a[x+3][y+7] < k && a[x+3][y+8]  <k
        && a[x+4][y] >= k && a[x+4][y+1]>= k && a[x+4][y+2]>= k 
        && a[x+4][y+3]>=k && a[x+4][y+4]>= k && a[x+4][y+5]>= k 
        && a[x+4][y+6]>=k && a[x+4][y+7] < k && a[x+4][y+8] < k){
            return 1;
        }
    return 0;
}