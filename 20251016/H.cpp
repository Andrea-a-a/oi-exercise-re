#include <bits/stdc++.h>
using namespace std;

int n, m, q;
struct edge{
    int u, v;
    long long c;
}edge[200010];

long long w[520];
long long dis[520][520];

long long query(int t);

//时间复杂度是q * n * n 感觉坏
int main(){
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        cin >> edge[i].u >> edge[i].v >> edge[i].c;
    }
    //无向图喵喵喵
    for(int i = 1; i <= m; i++){
        edge[i + m].u = edge[i].v;
        edge[i + m].v = edge[i].u;
        edge[i + m].c = edge[i].c;
    }
    cin >> q;
    //cout << "q!" << q << endl;
    for(int i = 0; i < q; i++){
        memset(w, 0, sizeof(w));
        memset(dis, 0x3f3f3f3f, sizeof(dis));
        int t;
        cin >> t;
        for(int o = 1; o < n; o++){
            cin >> w[o];
        }
        cout << query(t) << endl;
        //for(int i = 1; i <= n; i++)        cout << "dis[" << i << "] = " <<dis[i] << endl;
    }

    return 0;
}



long long query(int t){
    //最短路喵喵喵
    dis[1][1] = w[1];
    for(int i = 0; i < n; i++){
        bool flag = false;
        for(int o = 1; o <= 2*m; o++){
            long long temp = dis[edge[o].u][] + edge[o].c + w[edge[o].v];
            if(dis[edge[o].v] > temp)   dis[edge[o].v] = temp; flag = 1;
            //cout << "dis[" << edge[o].v << "] = " <<dis[edge[o].v] << "  " ;
        }
        if(!flag)   break;
    }
    
    return dis[t];
}