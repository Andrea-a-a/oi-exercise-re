#include <bits/stdc++.h>
// using namespace std;

// bool isFire[100000];
// int a[1];

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    //敌方有m个冰系n-m个火系
    int n, m;
    std::cin >> n >> m;
    std::vector<int> c,f;
    int ccnt{},fcnt{};
    for(int i{};i<n;i++){
        bool tag;
        int t;std::cin>>tag>>t;
        if(tag){
            fcnt++;
            f.push_back(t);
        }
        else{
            ccnt++;
            c.push_back(t);
        }
    }
    std::sort(f.begin(),f.end(),std::greater<int>());
    std::sort(c.begin(),c.end(),std::greater<int>());
    int cnum=std::min(ccnt,n-m);
    int fnum=std::min(fcnt,m);
    int ans=std::accumulate(c.begin(),c.begin()+cnum,0)*1.5
            +std::accumulate(c.begin()+cnum,c.end(),0)
            +std::accumulate(f.begin(),f.begin()+fnum,0)*2
            +std::accumulate(f.begin()+fnum,f.end(),0);
    std::cout<<ans<<std::endl;
    return 0;
}