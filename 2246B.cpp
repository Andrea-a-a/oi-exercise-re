#include <iostream>
#include <cmath>
using namespace std;

//注意直接输出会变成科学计数法，格式不对导致wawa

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;

        long long x = 3;

        if(n != 2){
            for(int i = 1; i <= n; i++){
                if(i == 1)  cout << "1 ";
                else if(i == 2) cout << "2 ";
                else{
                    cout << x << " ";
                    x *= 2;
                }
                
            }
            cout << endl;
        }
        else{
            cout << "-1" << endl;
        }


    }
    return 0;
}