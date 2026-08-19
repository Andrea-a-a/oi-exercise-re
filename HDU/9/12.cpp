#include <bits/stdc++.h>

using namespace std;
#define lowbit(x) (x&(-x))
const int MAXN = 1e5 + 7 ;



void solve(){
    int n;
    cin >> n;
    vector<int> a(n+1,0);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    long long ans = 0;
    if(n == 1 || n == 2){
        cout << '0' << '\n';
        return;
    }
    //枚举左右端点
    if(a[2]*a[1] +a[n]*a[n-1] > a[2]*a[n] + a[n-1]*a[1])    ans++;
    //枚举1和[3,n-1]交换
    for(int i = 3; i <= n-1; i++){
        if(a[2]*a[i] + a[1]*a[i+1] + a[i-1]*a[1] < a[2]*a[1] + a[i]*a[i+1] + a[i-1]*a[i]){
            ans++;
        }
    }
    //枚举n和[2, n-2]交换
    for(int i = 2; i <= n-2; i++){
        if(a[n-1]*a[i] + a[n]*a[i+1] + a[i-1]*a[n] < a[n-1]*a[n] + a[i]*a[i+1] + a[i-1]*a[i]){
            ans++;
        }
    }
    //枚举相邻的
    for(int i = 1; i <= n-1; i++){
        if((a[i+1] - a[i]) * (a[i+2] - a[i-1]) > 0) ans++;
    }

    //剩下的……

    //离散化
    vector<int> B;
    for(int i = 2; i <= n-1; i++){
        B.push_back(a[i-1]+a[i+1]);
    }
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());

    vector<pair<int, int>> Points;

    for(int i = 2; i <= n-1; i++){
        int b = a[i+1] + a[i-1];
        int ind = lower_bound(B.begin(), B.end(), b) - B.begin() + 1;
        Points.push_back({a[i], ind});
    }
    sort(Points.begin(), Points.end());

    int m = B.size();
    long long ans2 = 0;

    vector<int> tr(m+1, 0);


    for (int l = 0; l < m; ) {
        int r = l;
        while (r < m && Points[r].first == Points[l].first) r++;

        // 第一步：这一批点全部先查询（统计之前 a 更小的点）
        for (int k = l; k < r; k++) {
            	int s = 0 ;
                int u = Points[k].second-1;
                while (u > 0) {
                    s += tr[u] ;
                    u -= lowbit(u) ;
                }
            ans2 += s;
        }

        // 第二步：这一批点全部再插入
                for (int k = l; k < r; k++) {
                    int u = Points[k].second;
                        	while (u <= n) {
                        tr[u] += 1 ;
                        u += lowbit(u) ;
                            }
             }

        l = r; // 处理下一批 a 值
    }

    for(int i = 2; i <= n-2; i++){
        if((a[i] - a[i+1]) * (a[i+1] + a[i-1] - a[i+2] - a[i]) > 0) ans2--;
    }

    cout << ans + ans2 << endl;

    
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}







