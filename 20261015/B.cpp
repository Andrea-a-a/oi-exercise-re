#include<bits/stdc++.h>
using namespace std;
int T;
long long ppm, a, b, c, d, e, f;
int main(){
    scanf("%d", &T);
    while(T--){
        cin >> ppm >> a >> b >> c >> d >> e >> f;
        double acc;
        acc = 300 * (a + b) + 200 * c + 100 * d + 50 * e;
        acc = acc / 3;
        acc = acc / ((a + b + c + d + e + f) * 1);
        //cout <<fixed<<setprecision(2)<<acc << "%"<<endl;
        double pp;
        pp = 320 * a + 300 * b + 200 * c + 100 * d + 50 * e;
        pp *= ppm;
        pp /= 64; pp /= ((a + b + c + d + e + f) * 1);
        pp -= 4 * ppm;
        //pp += 0.5;
        pp = max(pp, 0.0);
        //printf("%lld\n", (int)pp);
        long long o1 = round(acc * 1e9); 
        long long o2 = round(pp * 1e9);
        printf("%.2f%% %.0f\n", o1 / 1e9, o2 / 1e9);
    }
    return 0;
}
