#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n; 
    long long w;
    cin >> n >> w;
    string s;
    cin >> s;

    cout << "Yes" << endl;
    
    cout << w << " ";
    int index = 0;
    while(s[index] == '&' && index < n){
        cout << w << " ";
        index++;
    }

    for(;index < n-1; index++){
        cout << "0 " ;
    }
    cout << endl;

}

int main(){

    int t;
    cin >> t;

    while(t--){
        solve();
    }


    return 0;
}