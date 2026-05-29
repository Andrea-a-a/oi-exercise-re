#include <iostream>
using namespace std;

int t;

int main(){

    cin >> t;
    while(t--){
        int n;
        cin >> n;

        if(n % 2 == 0){
            cout << n << " ";
        }
        else{
            cout << n-1 << " ";
        }
        for(int i = 2; i < n; i++){
            if(i % 2 == 0){
                cout << i+1 << " ";
            }
            else{
                cout << i-1 << " ";
            }
        }
        cout << "1" << endl;

    }


    return 0;
}