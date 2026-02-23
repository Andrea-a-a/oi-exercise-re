#include <iostream>

using namespace std;

int t;

int main(){
    cin >> t;
    for(int i = 0; i < t; i++){
        int n;
        string s;
        cin >> n >> s;
        int sumOne = 0;
        for(int o = 0; o < n; o++){
            if(s[o] == '1'){
                sumOne++;
            }
        }

        int sumZero = n - sumOne;
        



        if(sumOne % 2 == 1 && sumZero % 2 == 0){
            cout << "-1" << endl;
        }
        else if(sumOne % 2 == 0){
            cout << sumOne << endl;
            for(int o = 0; o < n; o++){
                if(s[o] == '1'){
                    cout << o+1 << " ";
                }
            }
            if(sumOne > 0){
                cout << endl;
            } 
        }
        else if(sumZero % 2 == 1){
            cout << sumZero << endl;
            for(int o = 0; o < n; o++){
                if(s[o] == '0'){
                    cout << o+1 << " ";
                }
            }
            if(sumZero > 0){
                cout << endl;
            } 
        }


    }




    return 0;
}