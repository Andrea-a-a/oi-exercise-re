#include <iostream>
using namespace std;

int main(){

    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int o;
        cin >> o;
        for(;o > 0;o--){
            cout << o << " ";
        }
        cout << endl;
    }

    return 0;
}