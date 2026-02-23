#include <iostream>
using namespace std;

int t;

int main(){
    cin >> t;



    for(int i = 0; i < t; i++){
        int n;
        string s;
        cin >> n >> s;

        int len = n;
        bool isBlock= 0;
        bool isSameEnd = 0;

        for(int o = 1; o < len; o++){
            if(s[o] == s[o-1]){
                isBlock = 1;
                break;
            }
        }

        int ans = 1;

        for(int o = 1; o < len; o++){
            if(s[o] != s[o-1]){
                ans++;
            }
        }        

        if(s[0] == s[len-1]){
            isSameEnd = 1;
        }

        if(!isBlock){
            cout << ans;
        }
        else if(isBlock && isSameEnd){
            cout << ans;
        }
        else{
            cout << ans+1;
        }

        cout << endl;


    }

    return 0;


}