#include <bits/stdc++.h>
using namespace std;

int a[1010], b[1010], cid[1010], ind[1010], idc[1010], cl[1010], rt[1010], dep[1010];

void ini(){
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(cid, 0, sizeof(cid));
    memset(ind, 0, sizeof(ind));
    memset(idc, 0, sizeof(idc));
    memset(cl, 0, sizeof(cl));
    memset(rt, 0, sizeof(rt));
    memset(dep, -1, sizeof(dep));
}

int dfs(int x){
    if(dep[a[x]] == -1){
        dfs(a[x]);
    }

    rt[x] = rt[a[x]];
    dep[x] = dep[a[x]] +1;
    cid[x] = cid[a[x]];
    return rt[x];
}

void solve(){
    int n;
    cin >> n;
    ini();
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        ind[a[i]]++;
    }
    for(int i = 1; i <= n; i++){
        cin >> b[i];
    }

    queue<int> ind0;
    for(int i = 1; i <= n; i++){
        if(ind[i] == 0){
            ind0.push(i);
        }
    }

    while(!ind0.empty()){
        int u = ind0.front();
        ind0.pop();
        ind[a[u]]--;
        if(ind[u] == 0)   ind0.push(a[u]);
    }

    //给环编号，从1开始
    int cincnt = 1;
    for(int i = 1; i <= n; i++){
        if(ind[i] != 0 && cid[i] == 0){

            //从i进行环的遍历
            int u = i, v = a[i];
            cid[i] = cincnt;
            idc[i] = 1, cl[cid[i]] = 1;
            rt[u] = u, dep[u] = 0;
            while(v != i){
                rt[v] = v, dep[v] = 0;
                cid[v] = cincnt;
                if(idc[v] == 0){
                    idc[v] = idc[u] +1;
                }
                u = v;
                v = a[u];
                cl[cid[i]] ++;
            }
            cincnt++;
        }
        
    }

    //计算树节点去环上的dep和rt
    for(int i = 1; i <= n; i++){
        if(dep[i] == -1){
            dfs(i);
        }
    }


    //test
    for(int i = 1; i <= n; i++){
        cout << "i = " << i << " cid = " << cid[i] << " rt = " << rt[i] << " dep = " << dep[i] << endl; 
    }

    //对b判定可行性
    int prevp = -2;
    int p = -1;
    for(int i = 1; i <= n; i++){
        //b[i]在树上
        if(dep[b[i]] > 0){
            //i也在树上
            if(dep[i] > 0){
                if(rt[i] != rt[b[i]] || rt[i] != rt[b[i]]){
                    cout << "-1" << endl;
                    return;
                }
                
                p = dep[i] - dep[b[i]];
                if(prevp == -2){
                    prevp = p;
                }
                if(p < 0 || p != prevp){
                    cout << "-1" << endl;
                    return;
                }

            }
            else{
                //i在环上
                //完全不可能！
                cout << "-1" << endl;
                return;
            }
        }
        else{
            
        }
    }


}


int main(){
    int t;
    cin >> t;

    while(t--){
       solve();
    }


    return 0;
}