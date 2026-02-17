#include <bits/stdc++.h>
using namespace std;

int n, q;
unsigned int prime[10000020];
bool isPrime [100000020];


int main(){
    ios::sync_with_stdio(0);
    memset(isPrime, 1, sizeof(isPrime));
    cin >> n >> q;
    //欧拉筛
    isPrime[1] = 0;
    int cnt = 0;
    for(int i = 2; i <= n; i++){
        if(isPrime[i]){
            cnt++;
            prime[cnt] = i;
            //cout << "prime is :" << i << endl;
        }
        for(int o = 1; o <= cnt&&i * prime[o] <= n ; o++){
            isPrime[i * prime[o]] = 0;
            if(i % prime[o] == 0)   break;

        }
    }


    for(int i = 0; i < q; i++){
        int k;
        cin >> k;
        cout << prime[k] << endl;
    }

    return 0;
}