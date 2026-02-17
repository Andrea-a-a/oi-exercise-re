#include <iostream>
using namespace std;


int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        int ans = 0;
        string s;
        int len;
        cin >> len;
        cin >> s;
        
        for(int o = len-1; o >= 0; o--){
            if(s[o]!=s[len-1])  ans++;
        }
        cout << ans << endl;
    }

    return 0;
}