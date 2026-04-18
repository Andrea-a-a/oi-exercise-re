#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

int main(){

    ull w;
    cin >> w;
    for(int i = 31; i >= 1; i--){
        ull sum = 0;
        //bool yee = 0;
        for(int o = 1; ; o++){
            sum += pow(o, i);
            if(sum == w){
                for(int q = 1; q < o; q++){
                    cout << q << '^' << i << '+';
                }
                cout << o << '^' << i ;
                return 0;
            }
            if(sum>w){
                break;
            }
        }
    }

    cout << "Impossible for " << w<<".";



    return 0;
}