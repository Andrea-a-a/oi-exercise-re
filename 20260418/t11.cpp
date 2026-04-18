//进行一遍dfs。把最大的最小值和藏宝的终点记在vector里。
#include <bits/stdc++.h>
using namespace std;

int n;
int w[100100];
int fa[100100];
int sonsize[100100];

//对于走到i的路径的最小值为ans[i]
int ans[100100];
vector<int> son[100100];
bool isZhong[100100];

int zhi = -1;
vector<int> zhong;


int prtcnt = 0;

void prt(int d){
    if(prtcnt == 0){
        cout << d;
    }
    else{
        cout << " " << d;
    }
    prtcnt++;
}

void dfs(int index){
    if(sonsize[index] == 0){
        //index是终点
        zhong.push_back(index);
        isZhong[index] = 1;


        ans[index] = min(w[index], ans[fa[index]]);
        zhi = max(ans[index], zhi);
        cout << "current: " << index << "ans is" << ans[index] << endl;
        return;
    }
    else{
        ans[index] = min(w[index], ans[fa[index]]);
        cout << "current: " << index << "ans is " << ans[index] << endl;
        for(int i = 0; i < sonsize[index]; i++){
            dfs(son[index][i]);
        }
    }



}




int main(){
    cin >> n;
    w[0] = 102;
    ans[0] = 102;
    for(int i = 1; i < n; i++){
        int tmp;
        cin >> tmp;

        fa[i] = tmp;
        son[tmp].push_back(i);
        sonsize[tmp]++;
        cin >> w[i];
    }

    dfs(0);
    cout << zhi << endl;

    /*
    int tmpsz = zhong.size();
    for(int i = 0; i < tmpsz; i++){
        if(ans[zhong[i]] == zhi){
            prt(zhong[i]);
        }
    }
    */

    for(int i = 1; i < n; i++){
        if(isZhong[i] && ans[i] == zhi){
            prt(i);
        }
    }



    return 0;
}
