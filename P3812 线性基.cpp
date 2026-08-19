#include <iostream>
using namespace std;

const int MAXA = 55, MAXN = 55;

long long a[MAXN+1], p[MAXA+1];

void insert(long long x){
    for(int i = MAXA; i >= 0; i--){
        if((x >> i) == 0){
            continue;
        }
        else if(p[i] == 0){
            p[i] = x;
            return;
        }
        else{
            x = x ^ p[i];
        }
    }
}

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        insert(a[i]);
    }
    long long ans = 0;
    for(int i = MAXA; i >= 0; i--){
        ans = max(ans, ans ^ p[i]);
    }
    cout << ans << endl;
    return 0;
}