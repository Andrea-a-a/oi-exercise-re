#include <iostream>
using namespace std;


int main(){
    long long t;
    cin >> t;
    for(long long i = 0; i < t; i++){
        long long a, b, n;
        cin >> a >> b >> n;
        if(n == 1)          cout << "1" << endl;
        else if(n * b <= a) cout << "1" << endl;
        else if(b == a)     cout << "1" << endl;
        else                cout << "2" << endl;

    }



    return 0;
}