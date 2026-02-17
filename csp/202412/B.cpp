#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+10;
int n;
long long a[MAXN], b[MAXN], asum[MAXN], bsum[MAXN], w[MAXN];
long long maxf[MAXN], maxb[MAXN];



int main(){
    cin >> n;
    for(int i = 0; i <= n; i++) {
        cin >> a[i];
        if(i > 0)        asum[i] = asum[i-1]+a[i];
        else asum[i] = a[i];
    }
    for(int i = 1; i <= n; i++){
        cin >> b[i];
        bsum[i] = bsum[i-1] + b[i];
    }
    maxf[0] = a[0];
    for(int i = 1; i <= n; i++){
        maxf[i] = max(maxf[i-1], asum[i] - bsum[i]);
    }
    maxb[n] = asum[n] - bsum[n];
    for(int i = n-1; i >= 0; i--){
        maxb[i] = max(maxb[i+1], asum[i]-bsum[i]);
    }


    for(int i = 1; i <= n; i++){
        w[i] = max(maxf[i-1], maxb[i]+b[i]);
        cout << w[i] << " ";
    }
    


    return 0;
}