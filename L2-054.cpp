#include <bits/stdc++.h>
using namespace std;
#define int long long


int n;
const int MAXN = 5e4+10;
// int x0[MAXN], x1[MAXN], x2[MAXN];
// int cnt0, cnt1, cnt2;


set<int> x0, x1, x2;

signed main(){

    ios::sync_with_stdio(0);

    cin >> n;
    for(int i = 0; i < n; i++){
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        if(tmp2 == 0){
            x0.insert(tmp1);
            //cnt0++;
        }
        else if(tmp2 == 1){
            x1.insert(tmp1);
            //cnt1++;
        }
        else if(tmp2 == 2){
            x2.insert(tmp1);
           // cnt2++;
        }
    }

    //sort(x0, x0+cnt0);
    //sort(x1, x1+cnt1);
    //sort(x2, x2+cnt2);
    //unique(x0, x0+cnt0);

    int first = 0;
    for(auto w : x1){
        //cout << "in x1:" << w << endl;
        for(auto e : x0){
            //cout << " in x0:" << e <<" to find:" << 2*w-e <<  endl;
            if(x2.find(2*w-e) != x2.end()){
                cout << '[' << e << ", 0]" << " [" << w << ", 1] [" << 2*w-e << ", 2]" << endl; 
                first++;
            }
            
        }
    }

    if(first == 0){
        cout << "-1";
    }


    // for(auto w : x2){
    //     cout << w << endl;
    // }




}