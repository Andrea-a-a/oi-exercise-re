#include <bits/stdc++.h>
using namespace std;
//lca

int n, m, s;
const int MAXN = 5e5+10;
int dep[MAXN], fa[MAXN][22];

vector<int> a[MAXN];
bool vis[MAXN];

int lca(int x, int y);
void dfs(int index, int f);
void inni(void);


int main(){
    ios::sync_with_stdio(0);
    cin >> n >> m >> s;
    dep[0] = -1;
    for(int i = 0; i < n-1; i++){
        int x, y;
        cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs(s, 0);
    inni();

    
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        //cout  << "       " << lca(x, y) << endl;
        cout  << lca(x, y) << endl;
    }
    
    return 0;
}

void dfs(int index, int f){
    vis[index] = 1;
    dep[index] = dep[f] +1;
    fa[index][0] = f;
    for(int i = 0; i < a[index].size() ; i++){
        if(!vis[a[index][i]]){
            dfs(a[index][i], index);
        }
    }
}

void inni(void){

	for(int j=1;j<=18;j++){
		for(int i=1;i<=n;i++){
			fa[i][j]=fa[fa[i][j-1]][j-1];
		}
	
}

}



int lca(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    //int delta = abs(x - y);
    for(int i = 18; i >= 0; i-- ){
        if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    }
    if(x == y)  return x;
    for(int i = 18; i >= 0; i--){
        if(fa[x][i] != fa[y][i]){
            x = fa[x][i];
            y = fa[y][i];
        }

    }
    return fa[x][0];
}