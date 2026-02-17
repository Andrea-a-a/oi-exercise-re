#include <bits/stdc++.h>
using namespace std;

int t;


int main(){
    cin >> t;
    for(int i = 0; i < t; i++){
        long long a, b, c, d, e, f = {};
        cin >> d >> e >> f;
        a = d | f;
        b = d | e;
        c = e | f;

        //cout << "| a&b = " <<( a&b) << " | b&c = " << (b&c) << " |c&a = " << (c&a) << '|' << endl;

        if((a & b) == d && (b & c) == e && (a & c) == f){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }



    }



    return 0;
}