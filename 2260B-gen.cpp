#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

// [l, r]
long long ra(long long l, long long r) {
    return rnd() % (r - l + 1) + l;
}


int main(){
    cout << "1\n";
    long long x = ra(1, 100000), y = ra(x, 300000), k = ra(0, 10000000);
    cout << x << " " << y << " "<< k << " " << endl;
}