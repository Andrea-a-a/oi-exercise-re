//并查集，压缩路径
#include <bits/stdc++.h>
using namespace std;

int n, m;
const int MAXN = 2e5+10;
int fa[MAXN];
//int id[MAXN];

void merge(int x, int y);
int find(int x);

int main(){
    cin >> n >> m;
    for(int o = 1; o <= n; o++){
        fa[o] = o;
        //id[o] = o;
    }
    for(int i = 0; i < m; i++){
        int opt, x, y;
        cin >> opt >> x >> y;
        if(opt == 1){

            if(find(x) != find(y))  merge(find(x), find(y));
        }    
        else{
            x = find(x);
            y = find(y);
            if(x == y)  cout << 'Y' << endl;
            else    cout << "N" << endl;
        }
    }


    return 0;
}



void merge(int x, int y){
    fa[x] = y;
}

int find(int x){
    if(fa[x] == x)  return x;
    else{
        
        return fa[x] = find(fa[x]);
    }
}