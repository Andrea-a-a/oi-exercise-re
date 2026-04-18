#include <bits/stdc++.h>
using namespace std;
#define int long long

//œ»–¥±©¡¶


int n, m;
int c[100100];
int cmx = -1;
vector<int> mx;

map<int, int> a;

void cha(int x){

    int tmpmin = 1e8+10;
    int index = 0;
    for(int i = 1; i <= n; i++){
        if(c[i] > x && c[i] < tmpmin){
            tmpmin = c[i];
            index = i;
        }
    }

    cout << index << endl;

}



signed main(){
    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> c[i];
        a.insert(make_pair(i, c[i]));
        if(c[i] > cmx){
            cmx = c[i];
            mx.clear();
            mx.push_back(i);
        }
        else if(c[i] == cmx){
            mx.push_back(i);
        }
    }

    int tmpsz = mx.size();
    int tmpcnt = 0;
    for(int i = 0; i < tmpsz; i++){
        if(tmpcnt == 0){
            cout << mx[i];
            tmpcnt++;
        }
        else{
            cout << " " << mx[i];
        }
    }
    cout << endl;

    cin >> m;
    while(m--){
        int tmpx;
        cin >>tmpx;
        cha(tmpx);
    }



    for(int i = 0; i < n; i++){
        cout << a[i] <<endl;
    }




    return 0;
}
