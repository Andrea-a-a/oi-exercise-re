#include <iostream>
using namespace std;

int t;

int main(){
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int cntl = 0, cntr = 0;
        while(n--){
            char w;
            cin >> w;
            if(w == '('){
                cntl++;
            }
            else{
                cntr++;
            }
        }
        if(cntl == cntr){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }





    return 0;
}