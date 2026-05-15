#include <iostream>
#include <math.h>

using namespace std;

int m, n;
int a[110][110];

int main(){

    cin >> n >> m;

    for(int i = 1; i <= n; i++){
        for(int u = 1; u <= n; u++){
            a[i][u] = 1200000;
        }
        a[i][i] = 0;
    }
    
    while(m--){
        int u, v, w;
        cin >> u >> v >> w;
        if(a[u][v] != 1200000){
            a[u][v] = min(a[u][v], w);
            a[v][u] = min(a[v][u], w);
        }
        else{
            a[u][v] = w;
            a[v][u] = w;
        }
    }

    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
            }
        }
    }

    for(int o = 1; o <= n; o++){
        for(int p = 1; p <= n; p++){
            cout << a[o][p] << ' ';
        }
        cout << endl;
    }


    return 0;
}