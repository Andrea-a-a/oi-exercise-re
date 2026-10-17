#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    vector<long long> v;
    if(t==1){
        long long n,l;
        cin>>n>>l;
        for(int i=0;i<n;i++){
            long long a;
            cin>>a;
            long long p=a/l;
            v.push_back(p);
        }
        sort(v.begin(),v.end(),greater<long long>());
        for(long long x:v){
            cout<<x<<" ";
        }
        cout<<endl;
    }
    if(t==2){
        long long n,k;
        cin>>n>>k;
        long long a[n];
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        long long sum=0;
        int flag=0;
        for(int i=0;i<n;i++){
            if(sum>=k){
                cout<<i<<endl;
                flag=1;
                break;
            }
            sum+=a[i];
        }
        if(flag==0){
            if(sum >= k){
                cout << n << endl;
            }
            else{
                cout<<-1<<endl;
            }
        } 
    }
    return 0;
}