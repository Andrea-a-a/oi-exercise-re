//使用vector来模拟stack
#include <bits/stdc++.h>
using namespace std;

int n, t;
vector<int> s;
int c[1010];

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

int main(){
    cin >> n >> t;



    for(int i = 1; i <= n; i++){
        cin >> c[i];
        if(c[i] > t){
            s.push_back(i);
        }
        else{
            prt(i);
        }
    }

    //cout << endl;

    while(s.size() > 0){
        int tmpsum = 0, sz = s.size();
        for(int i = 0; i < sz; i++){
            tmpsum += c[s[i]];
        }
        int tmpt = tmpsum / sz;
        for(int o = sz-1; o >= 0; o--){
            if(c[s[o]] <= tmpt){
                prt(s[o]);
                s.erase(s.begin()+o);
            }
            else{
                s.push_back(s[o]);
                s.erase(s.begin()+o);
            }
        }
    }



    return 0;
}
