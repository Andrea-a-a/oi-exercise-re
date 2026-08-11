#include <bits/stdc++.h>
using namespace std;

bool solve(){
    vector<int> t(16, 0);
    vector<bool>    b(16, false);
    vector<int> m(16, 0);
    vector<int> index[16];
    
    for(int i = 0; i < 33; i++){
        char tmp;
        cin >> tmp;
        if(tmp == 'T')  t[8]++;
        else if(tmp == 'J') t[9]++;
        else if(tmp == 'Q') t[10]++;
        else if(tmp == 'K') t[11]++;
        else if(tmp == 'A') t[12]++;
        else if(tmp == '2') t[13]++;
        else if(tmp == 'w') t[14]++;
        else if(tmp == 'W') t[15]++;
        else{
            t[tmp-'0'-2]++;
        }
    }

    if(t[14] == 0 && t[15] == 0){
        
        return false;
    }
    
    //出王炸
    if(t[14] == 2 && t[15] == 2){
        b[14] == true;
        b[15] == true;
    }

    //出炸弹
    for(int i = 13; i >= 1; i--){
        if(t[i] >= 4)   b[i] = true;
    }

    
    int cntelse = 0;
    for(int i = 1; i <= 15; i++){
        if(!b[i]){   m[t[i]]++; if(t[i] != 0)  cntelse++;}
    }

    if(m[1]!= 0){
        if(m[1] == 1)   {
            if(cntelse == 1)    return true;
            else    return false;
        }

    }

}

int main(){
    int t;
    cin >> t;
    while(t--){
        solve() ? cout << "YES" << endl : cout << "NO" << endl;
    }
}