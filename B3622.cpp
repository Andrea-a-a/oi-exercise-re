// 子集枚举
#include <iostream>
#include <vector>
using namespace std;
int n;
vector<char> w;

void dfs(int i){
    if(i == n){
        for(auto u : w){
            cout << u;
        }
        cout << endl;
        return;
    }
    w.push_back('N');
    dfs(i+1);
    w.pop_back();
    

    w.push_back('Y');
    dfs(i+1);
    w.pop_back();

}

int main(){
    
    cin >> n;

    
    dfs(0);   

}