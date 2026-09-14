#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int counteasy = 0;
        vector<int> a(n, 0);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            if(a[i] == 0)   counteasy++;
        }
        if(counteasy < 2)   cout << "-1\n";
        else if(a[0] == 0 && a[n-1] == 0)   cout << "0\n";
        else if(a[0] == 1 && a[n-1] == 1)   cout << "2\n";
        else    cout << "1\n";
    }
}