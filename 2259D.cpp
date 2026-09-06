#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin >> n;
    vector<long long> a(n);

    int zerocnt = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] == 0){
            zerocnt++;
        }
    }
    if(zerocnt == 1){
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    int index = 0;
    for(;index < n; index++){
        if(a[index] != 0){
            cout << 'C';
        }
        else{
            cout << 'A';
            break;
        }
    }
    index++;
    for(; index < n; index++){
        if(a[index] != 0){
            cout << 'C';
        }
        else{
            cout << 'B';
            
        }
    }
    cout << endl;
}

int main(){
    int n;
    cin >> n;
    while(n--){
        solve();
    }
    return 0;
}