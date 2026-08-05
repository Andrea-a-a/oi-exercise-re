#include <iostream>
using namespace std;

void solve(){
    int a, b, c;
    cin >> a >> b >> c;
    if(a < b){
        swap(a, b);
    }
    if(a < c){
        swap(a, c);
    }
    if(b < c){
        swap(b, c);
    }
    cout << min(a-b, b-c) << endl;
}


int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}