#include <bits/stdc++.h>
using namespace std;

long long n, N, q;

#define int long long

void read(int x);
void writ(int x);
int find(int x);
void zairu(int x);

//写链表。
struct node{
    int index;
    bool t;
    node *next;
    node *last;
};


vector<pair<int,bool>> que[65537];

signed main(){
    cin >> n >> N >> q;
    for(int i = 1; i <= q; i++){
        //cout << "指令第" << i << ":" ;
        int opt, index;
        cin >> opt >> index;
        if(opt == 0)    read(index);
        else    writ(index);
    }
    return 0;
}

void read(int x){
    int che = find(x);
    if(che == -1){
        zairu(x);
        che = find(x);
    }
    int index = (x / n)%N;
    bool i = que[index][che].second;
    que[index].erase(que[index].begin()+che);
    que[index].push_back(pair(x, i));
    
}

void writ(int x){
    int che = find(x);
    if(che == -1){
        zairu(x);
        che = find(x);
    }
    int index = (x / n)%N;
    //que[index][che].second = 1;
    que[index].erase(que[index].begin()+che);
    que[index].push_back(pair(x, 1));
}

//寻找x在不在缓存里，如果在缓存中，返回该组缓存vector中的位置，不在返回-1
//存在     ->  命中     在vector[i]中存着了
//不存在   ->  未命中
int find(int x){
    int index = (x / n)%N;
    int siz = que[index].size();
    for(int i = 0; i < siz; i++){
        if(que[index][i].first == x)  {
            //cout << "命中!" << endl; 
            return i;
        }
    }
    //cout << "未命中!"<<endl;
    return -1;
}

void zairu(int x){
    int index = (x / n)%N;
    if(que[index].size()< n){
        que[index].push_back(pair(x, 0));
    }   
    else{
        int index2 = que[index][0].first;
        if(que[index][0].second)    cout << "1 " << index2 << endl;
        que[index].erase(que[index].begin());
        que[index].push_back(pair(x,0));
    }
    cout << "0 " << x << endl;
    //cout << "已载入：" << x << " 当前已载入：" << que[index].size() << endl;
}