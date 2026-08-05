#include <iostream>
using namespace std;

void solve(){
    int minus = 0;
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = 1;
    for(int i = 1; i < n; i++){
        if(s[i] != s[i-1]){
            ans++;
        }
        
    }
    for(int i = 1; i < n-1; i++){
        if(s[i] != s[i-1] && s[i] != s[i+1] && s[i-1] == s[i+1]){
            minus = 2;
            cout << ans-minus << endl;
            return;
        }
        if(s[i] != s[i-1] && s[i] != s[i+1]){
            minus = 1;
        }
    }
    cout << ans - minus << endl;
    return;

}

int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}