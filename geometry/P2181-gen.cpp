#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int main(){
    cout << rnd() % (100000-3+1) + 3;
    return 0;
}
