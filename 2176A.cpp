#include <iostream>

using namespace std;

int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        int n;
        cin >> n;
        int a0, cnt;
        cin >> a0;
        cnt = 1;
        for(int i = 1; i < n; i++){
            int tmp;
            cin >> tmp;
            if(tmp >= a0){
                cnt++;
                a0 = tmp;
            }
        }
        cout << n - cnt << endl;
    }
    return 0;
}