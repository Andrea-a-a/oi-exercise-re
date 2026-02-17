#include <iostream>
#include <cstring>
using namespace std;

int t;
const int MAXN = 3e5+10;

long long f[MAXN];
long long b[MAXN];


void inni();

int main(){
    ios::sync_with_stdio(0);


    cin >> t;
    for(int i = 0; i < t; i++){
        //inni();
        int n;
        cin >> n;
        for(int o = 1; o <= n; o++){
            cin >> f[o];
        }
        b[n] = (f[n] + f[1]) / (n-1);
        
        cout << (f[2] - f[1] + b[n]) / 2 << " ";
        for(int o = 2; o < n; o++){
            cout << ((f[o+1] - f[o] + b[n]) / 2) - ((f[o] - f[o-1] + b[n]) / 2) << " ";
        }
        cout << b[n] - ((f[n] - f[n-1] + b[n]) / 2);
        cout << endl;
    }



    return 0;
}

void inni(){
    memset(f, 0, sizeof(f));
    memset(b, 0, sizeof(b));

}