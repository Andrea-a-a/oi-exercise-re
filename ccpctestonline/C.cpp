#include <bits/stdc++.h>
using namespace std;

int main(){
    long long n;
    cin >> n;
    vector<long long> a(n), b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    priority_queue<long long> c;
    long long cnt = 0, cur = 0;

    for(int i = 0; i < n; i++){
        //cerr<< "working on i = " << i << endl;
        cur += a[i];
        c.push(b[i]);
        if(cur < 0){
            while(cur < 0 && !c.empty()){
                cur += c.top();
                c.pop();
                cnt++;
            }
            if(cur < 0){
                cout << "-1";
                return 0;
            }
        }

    }

    cout << cnt;
    return 0;


}