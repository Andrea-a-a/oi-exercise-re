#include <bits/stdc++.h>
using namespace std;
int t;

int main(){
    cin >> t;
    for(int i = 0; i < t; i++){
        int n;
        cin >> n;
        long long max1, min1;
        max1 = -1e9-10;
        min1 = 1e9+10;
        long long temp, x;
        for(int o = 0; o < n; o++){
            cin >> temp;
            min1 = min(min1, temp);
            max1 = max(max1, temp);
        }
        cin >> x;
        if(x <= max1 && x >= min1)  cout << "YES" << endl;
        else cout << "NO" << endl;


    }



    return 0;
}