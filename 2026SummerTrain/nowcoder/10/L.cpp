#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    std::cin>>T;
    while(T--){
        int m,r,c;cin>>m>>r>>c;
        int cycle=m+r;
        int times=(c)/cycle;
        int bull=(1+times)*m;
        int tot=max(c,bull+times*r);

        cout<<std::fixed<<setprecision(9)<<(double)bull/tot<<"\n";

    }

}