#include <iostream>
using namespace std;

const int MAXN = 1e6+10;
int n, maxa;
long long m;
int a[MAXN];

bool check(int h) {
    long long sum = 0;
    for(int o = 0; o < n; o++) {
        if(a[o] > h){
            sum += a[o] - h;
        }
    }

    return sum >= m;
}

void solve(int l, int r) {
    int height;
    while(l + 1 < r) {
        height = (l + r) >> 1;
        if(check(height)) {
            l = height;
        }
        else {
            r = height;
        }

        

    }
    cout << l;



}

int main() {

    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        maxa = max(a[i], maxa);
    }

    //在[1, maxa+1)二分
    solve(1, maxa + 1);




    return 0;
}