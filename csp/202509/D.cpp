#include <bits/stdc++.h>
using namespace std;
const int MAXN= 2e5+10;

bool mex[MAXN];
int n, m;
int a[MAXN];

int mexx(int x, int y);
void build(int x, int y);

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for(int i = 1; i < n; i++){
        int x, y;
        cin >> x >> y;
        build(x, y);
    }
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        cout << mexx(x, y) << endl;
    }
    return 0;

}

void build(int x, int y){


    
}

int mexx(int x, int y){
    memset(mexx, 0, sizeof(mexx));







    return 0;
}