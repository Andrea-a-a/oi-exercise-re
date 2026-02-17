#include <iostream>
#include <cstring>
using namespace std;

void inni();

int t;
const int MAXN = 1e5+10;
long long ai[MAXN], bi[MAXN], ci[MAXN];
int cnt[MAXN];

int main(){
    cin >> t;
    for(int i = 0; i < t; i++){
        inni();
        int n;
        long long x;
        for(int i = 1; i <= n; i++){
            cin >> ai[i] >> bi[i] >> ci[i];
        }
    }
    
    return 0;
}

void inni(){
    memset(ai, 0, sizeof(ai));
    memset(bi, 0, sizeof(bi));
    memset(ci, 0, sizeof(ci));
    memset(cnt, 0, sizeof(cnt));
}

