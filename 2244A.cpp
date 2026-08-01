#include <iostream>
#include <string>

using namespace std;

int t;

void solve(){
    int n;
    cin >> n;
    char now;
    

    int maxnum = 0;
    int curnum = 0;

    while(n--){
        cin >> now;
        if(now == '*'){
            curnum = 0;
        }
        else{
            curnum++;
        }
        maxnum = max(maxnum, curnum);

        //last = now;
    }

    maxnum % 2 == 0 ? cout << maxnum/2 << endl : cout << maxnum/2 +1 << endl; 



}

int main(){
    cin >> t;
    while(t--){
        solve();

    }
    



    return 0;
}