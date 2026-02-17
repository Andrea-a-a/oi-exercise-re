#include <iostream>

using namespace std;
int t;

int main(){

    cin >> t;
    for(int i = 0; i < t; i++){
        int n;
        cin >> n;
        bool yes = 0;
        for(int o = 0; o < n; o++){
            int temp;
            cin >> temp;
            if(temp == 67){
                yes = 1;
            }
        }
        if(yes){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }

    return 0;
}