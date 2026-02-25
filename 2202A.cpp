#include <iostream>

using namespace std;

#define int long long

int t;



signed main(){
    cin >> t;
    for(int p = 0; p < t; p++){
        int x, y;
        cin >> x >> y;

        if(y == 0){
            if(x % 3 == 0){
                cout << "YES" << endl;
            }
            else{
                cout << "NO" << endl;
            }
        }
        else if(y > 0){
            x = x - y * 2;
            if(x < 0){
                cout << "NO" << endl;
            }
            else if(x % 3 == 0){
                cout << "YES" << endl;
            }
            else{
                cout << "NO" << endl;
            }
        }
        else{
            x = x + y * 4;
            if(x < 0){
                cout << "NO" << endl;
            }
            else if(x % 3 == 0){
                cout << "YES" << endl;
            }
            else{
                cout << "NO" << endl;
            }



        }



    }

    return 0;


}