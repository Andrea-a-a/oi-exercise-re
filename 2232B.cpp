#include <iostream>
#include <cstring>

using namespace std;

int t, n;
const int MAXN = 2e5+10;
long long sum[MAXN];

void inni() {
    n = 0;
    memset(sum, 0, sizeof(sum));
}


int main() {

    cin >> t;
    while(t--){
        inni();
        cin >> n;
        long long anstmp = 1e9+10;
        for(int i = 1; i <= n; i++){
            int tmp;
            cin >> tmp;
            sum[i] = sum[i-1] + tmp;
            anstmp = min(anstmp, sum[i]/i);
            cout << anstmp << " ";
        }
        cout << endl;

    }



    return 0;
}