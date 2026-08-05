#include <iostream>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int acnt1 = 0, acnt2 = 0, bcnt1 = 0, bcnt2 = 0;
        for(int i = 0; i < n; i++){
            char tmp;
            cin >> tmp;
            if(tmp == '1'){
                if(i % 2 == 0){
                    acnt1++;
                }
                else acnt2++;
            }
        }
                for(int i = 0; i < n; i++){
            char tmp;
            cin >> tmp;
            if(tmp == '1'){
                if(i % 2 == 0){
                    bcnt1++;
                }
                else bcnt2++;
            }
        }
        if(acnt1 == bcnt1 && acnt2 == bcnt2){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }
}