#include <iostream>
using namespace std;

int t;
int main(){
    cin >> t;

    while(t--){
        long long n, a, b;
        cin >> n >> a >> b;

        //cout << n << " " << a  << " " << b << endl;

        if(a * 3 <= b){
            cout << n * a << endl;
        }
        else{
            if(n%3==0){
                cout << b * (n / 3) << endl;
            }
            else{
                cout << b * (n / 3) + min((n%3) * a, b) << endl;
            }
        }

    }


    return 0;
}