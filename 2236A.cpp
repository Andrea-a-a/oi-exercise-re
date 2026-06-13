#include <iostream>
using namespace std;

int t;

int main(){

    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;


        //先写一个模拟
        for(int i = 0; i < n; i++){
            if(s[i] == '1'){
                if(i + k < n){
                    s[i] = '0';
                    if(s[i+k] == '1'){
                        s[i+k] = '0';
                    }
                    else{
                        s[i+k] = '1';
                    }
                }
            }
        }

        bool yess = 1;
        for(int i = 1; i <= k; i++){
            if(s[n-i] == '1'){
                yess = 0;
                cout << "NO" << endl;
                break;
            }
        }

        if(yess){
            cout << "YES" << endl;
        }


    }



    return 0;
}