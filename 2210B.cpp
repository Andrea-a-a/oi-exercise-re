#include <iostream>
using namespace std;

int t;

int main(){

    cin >> t;
    for(int w = 0; w < t; w++){
        int n;
        int p[200010];
        int ans = 0;
        cin >> n;

        for(int i = 1; i <= n; i++){
            cin >> p[i];
            if(p[i] <= i){
                ans++;
            }

        }
        cout << ans << endl;
    }
    //不一定是正解




    return 0;
}