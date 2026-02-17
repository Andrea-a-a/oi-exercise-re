//B3644 but dfs
#include <bits/stdc++.h>
using namespace std;

void dfs(int index);

vector<int> gra[101];
bool vis[101];
int n;
stack<int> s;

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        int temp;
        while(true){
            cin >> temp;
            if(temp == 0)   break;
            gra[i].push_back(temp);
        }
    }
    //cout << gra[1].size()<<"miao" << endl;
    dfs(1);
    for(int o = 1; o <= n; o++){
        if(!vis[o]) dfs(o);
    }
    for(int i = 0; i < n; i++){
        cout << s.top() << " ";
        s.pop();
    }


    return 0;
}

void dfs(int index){
    vis[index] = true;
    for(int i = 0; i < gra[index].size(); i++){
        if(!vis[gra[index][i]]){
            dfs(gra[index][i]);
        }

    }
    s.push(index);

}