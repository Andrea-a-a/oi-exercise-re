#include <iostream>
using namespace std;

int t;

int main(){

    cin >> t;
    for(int i = 0; i < t; i++){
        int n, s, x;
        cin >> n >> s >> x;
        int sum = 0;
        int temp;
        for(int i = 0; i < n; i++){
            cin >> temp;
            sum += temp;
        }

        if(s < sum){
            cout << "NO" << endl;
        }
        else if(((1.0 * s - sum)/x - ((s-sum)/x)) != 0){
            cout << "NO" << endl;
        }
        else{
            cout << "YES" << endl;
        }


    }



    return 0;
}