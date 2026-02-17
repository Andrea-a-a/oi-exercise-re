#include <bits/stdc++.h>
using namespace std;

vector<int> a[101];
int in[101];
int n;

int main(){
    cin >> n;
    queue<int> q;
   
    for(int i = 1; i <= n; i++){
        int temp;
        while(true){
            cin >> temp;
            if(temp == 0)   break;
            a[i].push_back(temp);
            in[temp]++;

        };
        
    }
    for(int w = 1; w <= n; w++){
        if(in[w] == 0){
            q.push(w);
        }
    }
    while(!q.empty()){
        int f = q.front();
        cout << f << " ";
        for(int o = 0; o < a[f].size(); o++){
            in[a[f][o]]--;
            if(in[a[f][o]] == 0)    q.push(a[f][o]);
        }

        q.pop();
    }
    return 0;

}