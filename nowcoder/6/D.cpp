#include <bits/stdc++.h>
using namespace std;

// int a[500100][500100];

// void ini(){
//     memset(a, 0, sizeof(a));
// }

const int big = 5e6;

void solve(){
    //ini();
    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<vector <int>> a(n+1);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    //bfs
    vector<int> d0(n+1, big), d1(n+1, big);
    d0[1] = 0;
    queue<pair<int, int>> q;
    q.push(pair(1, 0));
    while(!q.empty()){
        int i = q.front().first;
        int w = q.front().second;
        int di = (w == 0 ? d0[i] : d1[i]);
        q.pop();
        for(auto v : a[i]){
            if(w == 1){
                if(d0[v] == big){
                    d0[v] = di+1;
                    q.push(pair(v, 0));
                }

            }
            else{
                if(d1[v] == big){
                    d1[v] = di+1;
                    q.push(pair(v, 1));
                }
            }
        }
    }

    //对每个点找出d
    cout << "0 ";
    for(int i = 2; i <= n; i++){
        //对于偶数长度
        long long ans = (1LL << 62);
        if(d0[i] < big){
            long long x = (d0[i] + k - 1) / k;

            if (k % 2 == 1) {
                if (x % 2 == 1) x++; // k为奇数时，q必须为偶数，才能让 q*k 为偶数
            }
            ans = min(ans, x * k);
        }

        if(d1[i] < big){
            if(k % 2 == 1){
                long long x = (d1[i] + k - 1) / k;
                if(x % 2 == 0)  x++;
                ans = min(ans, x * k);
            }
        }

        if(ans == (1LL << 62))  cout << "-1 " ;
        else    cout << ans << " ";

    }

    cout << endl;

    
}

int main(){

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}