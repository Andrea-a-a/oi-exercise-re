#include <bits/stdc++.h>
using namespace std;

int n;
const int MAXN = 1e5+10;
int len1[MAXN];
int len2[MAXN];
vector<int> chi[MAXN];
bool vis1[MAXN];
bool vis2[MAXN];

void dfs1(int i);
void dfs2(int i);

int main(){
    cin >> n;
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        chi[u].push_back(v);
        chi[v].push_back(u);
    }
    int maxx=1;
    int maxl=0;
    dfs1(1);
    for(int i = 2; i <= n; i++){
        if(len1[i] > maxl){
            maxl = len1[i];
            maxx = i;
        }
    }
    //cout << "max1:" << max << " maxl:" << maxl;
    //int max2 = 0;  
    dfs2(maxx);
    int maxl2 = 0;
    for(int i = 1; i <= n; i++){
        maxl2 = max(maxl2, len2[i]);
    }
    cout << maxl2;

    //int ans = abs(max2-max)+1;
    

    //cout << ans;

    return 0;
}

void dfs1(int i){
    vis1[i] = 1;
    for(int o = 0; o < chi[i].size(); o++){
        if(!vis1[chi[i][o]]){
            len1[chi[i][o]] = len1[i]+1;
            dfs1(chi[i][o]);}
    }
}

void dfs2(int i){
    vis2[i] = 1;
    for(int o = 0; o < chi[i].size(); o++){
        if(!vis2[chi[i][o]])        {
            len2[chi[i][o]] = len2[i]+1;
            dfs2(chi[i][o]);
        }
    }
}