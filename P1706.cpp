#include <bits/stdc++.h>
using namespace std;
int n;

int main(){

    cin >> n;
    vector<int> o;
    for(int i = 1; i <= n; i++){
        o.push_back(i);
    }
    do{
        for(auto w : o) cout << setw(5) << w;
        cout << endl;

    }while(next_permutation(o.begin(), o.end()));

}