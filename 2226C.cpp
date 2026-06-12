#include <iostream>
#include <algorithm>
using namespace std;

int t, n;
int a[200010], found[200010];
bool used[200010];

int solve(){
    int index = n/2, l = 0, r = n;
    while(l < n){
        index = (l + r) >> 1;
        if(ok(index)){
            l = index;
        }
        else{
            r = index+1;
        }
    }

    return index;

    
}

bool ok(int f){

    for(int o = f-1; o >= 0; o--){
        for(int i = n-1; i >= 0; i--){
        if(!found[a[i]]){
            used[i] = 1;
            found[a[i]] = 1;
        }
        else{

        }
        }
    }



}

int main(){
    cin >> t;
    while(t--){
        
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            used[i] = 0;
            found[i] = 0;
        }

        sort(a, a+n);

        int ans = 0;
        

        //二分。
        ans = solve();

    }
    return 0;
}