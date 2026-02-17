#include <bits/stdc++.h>
using namespace std;

int n;
double r, theta;
double rr[100101];
const double PI = 3.1415926;


int main(){
    ios::sync_with_stdio(0);
    
    cin >> n;
    cin >> r >> theta;
    for(int i = 1; i <= n; i++){
        cin >> rr[i];
    }

    theta = min(theta, 2*PI-theta);
    //cout << theta<<endl;
    double ans = 0;
    sort(rr+1, rr + n+1);
    //cout << "rr!~" << rr[1] << endl;
    if(theta > 2){
        ans = 2*r + theta* rr[1] - 2 * rr[1];
    }
    else{
        ans = theta * r;
    }

    //cout << ans;
    printf("%.10f", ans);



    return 0;
}