#include <bits/stdc++.h>
using namespace std;

char a[6][6];
int b[6][6];
bool opened[6][6], knew[6][6];
int n, m;
vector<pair<int, int>> safe;


void ini(){
    safe.clear();
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(opened, 0, sizeof(opened));
    memset(knew, 0, sizeof(knew));
}

//获取(u, v)这个坐标合不合法，合法返回true
bool isin(int u, int v){
    if(u < 0 || u > n-1 || v < 0 || v > m-1)    return 0;
    else{
        return 1;
    }
}

//获取(u,v)是不是雷，是返回1
int req(int u, int v){
    if(!isin(u, v)) return 0;
    if(a[u][v] == '#'){
        return 1;
    }
    return 0;
}

//获取(u,v)是不是已知的地雷，是返回1
int req3(int u, int v){
    if(req(u, v) != 1)  return 0;

    if(knew[u][v])  return 1;
}


//获取(u, v)是不是开着的，是返回1
int req2(int u, int v){

    if(!isin(u, v)) return 0;
    if(opened[u][v]){
        return 1;
    }

    return 0;
}

//初始化计算每个翻开有数的块的数字
void calcnum(){
    for(int i = 0; i < n; i++){
        for(int o = 0; o < m; o++){
            if(a[i][o] == 'O' || a[i][o] == '.'){
                b[i][o] += req(i-1, o) + req(i+1, o) + req(i-1, o-1) + req(i-1, o+1)
                            + req(i+1, o-1)+ req(i+1, o+1)+req(i, o+1) + req(i, o-1);
            }
        }
    }
}

bool findsafe(){

    if(safe.empty())    return false;
}

//打开(i, o)并且更新已知的雷区
void onk(int i, int o){
    opened[i][o] = true;
    int all = getall(i, o), open = getopen(i, o);
    if(all - open == b[i][o]){
        //标记，(i, o)边上所有的雷都知道了
    }

}

int getknew(int i, int o){
    int ans = req3(i-1, o) + req3(i+1, o) + req3(i-1, o-1) + req3(i-1, o+1)
                            + req3(i+1, o-1)+ req3(i+1, o+1)+req3(i, o+1) + req3(i, o-1);
    return ans;
}

//获取(i, o)周围有几个开着的方块
int getopen(int i, int o){
    int ans = req2(i-1, o) + req2(i+1, o) + req2(i-1, o-1) + req2(i-1, o+1)
                            + req2(i+1, o-1)+ req2(i+1, o+1)+req2(i, o+1) + req2(i, o-1);
    return ans;
}

//获取(i, o)周围有几个方块
int getall(int i, int o){
    if((i == 0 && o == 0) || (i == 0 && o == m-1) 
        || (i == n-1 && o == 0) || (i == n-1 && o == m-1)){
        return 3;
    }
    else if(i == 0 || i == n-1 || o == 0 || o == m-1 ){
        return 5;
    }
    else{
        return 8;
    }
}




void solve(){
    cin >> n >> m;
    ini();
    for(int i = 0; i < n; i++){
        for(int o = 0; o < n; o++){
            cin >> a[i][o];
        }
    }
    calcnum();
    //初始化open and knew
    for(int i = 0; i < n; i++){
        for(int o = 0; o < n; o++){
            if(a[i][o] == 'O')  onk(i, o);
        }
    }


    /*  直到游戏结束（true）或者找不到安全格子（-1）
        1. 根据现在的状态，找到安全格子
            a. 直接推理得出这个地方是安全格子
                对于一个已经翻开的有标号方块，
                if(周围已知雷数 == 号码)  剩下的都是好方块；
                else if(周围已翻开方块剩下的块数 == 雷数) 剩下的都是地雷。
            b. 枚举所有的地雷情况，这个地方都不可能是雷
                先设这个地方是雷，再看能否推导出矛盾
        2. 翻开安全格子
            更新已翻开的状态，更新已知的雷的位置
    */


}

int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}