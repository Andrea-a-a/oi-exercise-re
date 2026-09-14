#include <bits/stdc++.h>
using namespace std;

int t;

void solve(){
    int n, k, m, q;
    cin >> n >> k >> m >> q;
    unordered_map<string, int> a, b, index;
    string tmp, last;
    int contcnt = 1;
    bool said = 0;
    for(int i = 1; i <= n; i++){
        cin >> tmp;
        if(a.find(tmp) == a.end()){
            a[tmp] = 1;
            b[tmp] = 1;
            index[tmp] = i;
            contcnt = 1;
            
        }
        else{


            //判断，在这句话说出之前是否有可能是ind说的
            if(b[tmp] < q && i - index[tmp] > m && a[tmp] >= k){
                cout << i << " ";
                said = 1;
            }


            b[tmp]++;
            if(tmp == last){
                contcnt++;
                a[tmp] = max(a[tmp], contcnt);
                
            }
            else{
                contcnt = 1;
            }            
        }


        

        last = tmp;
    }
    if(!said){
        cout << "empty";
    }
    cout << endl;
}

int main(){

    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}