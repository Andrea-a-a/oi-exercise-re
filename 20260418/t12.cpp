//图的贪心？遍历
//还是先写暴力吧！
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4+10;
int a[MAXN][MAXN];
int n, m;
bool isVisited[MAXN];
vector<int> son[MAXN];
int sonsize[MAXN];


void think(int index){
    isVisited[index] = 1;
    if(sonsize[index] == 0){
        //是终点
        cout << index;
        return;
    }
    else{
            //寻找最大的下一个
            cout << index <<"->";
            int tmpmax = 0;
            int tmpindex = -1;
            for(int i = 0; i < sonsize[index]; i++){
                    if(!isVisited[son[index][i]]){
                        if(a[index][son[index][i]] > tmpmax){
                            tmpmax = a[index][son[index][i]];
                            tmpindex = son[index][i];
                        }
                    }
            }
           think(tmpindex);


    }



}




int main(){

    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int tmp1, tmp2;
        cin >>tmp1 >> tmp2;
        son[tmp1].push_back(tmp2);
        sonsize[tmp1]++;

        cin >> a[tmp1][tmp2];

    }

    int k;
    cin >> k;
    while(k--){
        int tmpp;
        cin >> tmpp;
        think(tmpp);
        cout << endl;
    }

    return 0;

}
