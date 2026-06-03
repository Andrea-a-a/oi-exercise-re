#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int t, n;
long long a[110];

void inni() {
    n = 0;
    memset(a, 0, sizeof(a));

}


int main() {

    cin >> t;
    while(t--) {
        cin >> n;

        for(int i = 1; i <= n; i++){
            cin >> a[i];
        }
        sort(a+1, a+1+n);


        if(n % 2 == 0){
            int tmp = a[n/2];
            int cnt = 0;
            while(a[n/2-cnt] == a[n/2+1+cnt] && a[n/2-cnt] == tmp){
                cnt++;
            }
            cout << n/2 - cnt << endl;

        }
        else{
            int cnt = 0;
            while(a[n/2-cnt] == a[n/2+cnt+2] && a[n/2-cnt] == a[n/2+1]){
                cnt++;

            }
            cout << n/2 - cnt << endl;
        }




    }



}