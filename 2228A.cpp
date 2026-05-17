#include <iostream>
#include <math.h>
using namespace std;

int main(){

    int n;
    cin >> n;
    while(n--){
        int m;
        cin >> m;
        int cnt0 = 0, cnt1 = 0, cnt2 = 0;
        while(m--){
            int temp;
            cin >> temp;
            if(temp == 0){
                cnt0++;
            }
            else if(temp == 1){
                cnt1++;
            }
            else if(temp == 2){
                cnt2++;
            }
        }
        cout << cnt0 + min(cnt1, cnt2) + (cnt1 - min(cnt1, cnt2))/3 + (cnt2 - min(cnt2, cnt1))/3 << endl;
    }

    return 0;
}