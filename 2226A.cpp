#include <iostream>
using namespace std;

int t;
const int MOL = 676767677;

int main(){

    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int sum = 0;
        //bool haveOne = 0;
        while(n--){
            int tmp;
            cin >> tmp;
            
            if(tmp != 1){
                
                sum += tmp;
                sum %= MOL;
            }
            else{
                if(n==0){
                    sum += tmp;
                    sum %= MOL;
                    
                }
            }
        }
        cout << sum << endl;
    }

    return 0;

}