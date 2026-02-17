#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[10010];

int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        cin >> a[i];
    }
    for(int i = 2; i <= n; i++){
        for(int o = 1; o < i; o++){
            if(a[i] < a[o] + a[i-o])    a[i] = a[o] + a[i-o];
        }
    }
    cout << a[n];

    return 0;
}