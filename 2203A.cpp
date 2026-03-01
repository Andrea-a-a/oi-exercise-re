#include <iostream>
using namespace std;

int t;


int main(){
    cin >> t;
    for(int w = 0; w < t; w++){

        int n, m, d;
        cin >> n >> m >> d;

        if( n % (d/m + 1) == 0 ){
            cout << n/(d/m + 1) << endl;
        }
        else{
            cout << n/(d/m + 1) + 1 << endl;
        }



    }

    return 0;
}