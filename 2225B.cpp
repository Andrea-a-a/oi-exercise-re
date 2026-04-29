#include <iostream>

using namespace std;

int main(){

    int t;
    cin >> t;
    while(t--){

        string s;
        cin >> s;
        //检测到两个相同字母自动+1！
        int ans = 0;
        int len = s.length();
        for(int i = 0; i < len-1; i++){
            if(s[i] == s[i+1]){
                ans++;
            }
            if(ans >= 3){
                cout << "NO" << endl;
                break;
            }
        }
        if(ans < 3){
            cout << "YES" << endl;
        }

        
    }




    return 0;
}