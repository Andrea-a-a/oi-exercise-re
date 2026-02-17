#include <bits/stdc++.h>
using namespace std;


int n, a;
//double x[1010], y[1010];
int main(){
    cin >> n >> a;
    int cnt = 0;
    for(int i = 0; i < n; i++){
        double o, p;
        cin >> o >> p;
        //cout << o*o + p*p <<" " << a*a << endl;
        if(o*o + p*p <= a*a) cnt++;
    }
    double ans = 4.0*cnt/n;
    printf("%.6f", ans);

    


    return 0;
}