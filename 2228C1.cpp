#include <iostream>
#include <math.h>
using namespace std;

int getlen(int a);

int main(){

    //cout << getlen(1999) << endl;

    int t;
    cin >> t;
    while(t--){

        int a, n, x, y;
        cin >> a >> n >> x >> y;

        if(x > y){
            swap(x, y);
        }

        int len = getlen(a);
        //cout << getlen(a) << endl;

        if(len == 1){
            cout << min(abs(a-x), abs(a-y)) << endl;
        }
        else{
            // int ans1;
            // if(x != 0){
            //     ans1 = x;
            //     for(int i = 0; i < len; i++){
            //         ans1 = ans1 * 10 + x;
            //     }
            // }
            // else{
            //     ans1 = y * pow(1, len);
            // }
            // cout << ans1 << " ";
            // int ans2 = y;
            // for(int i = 0; i < len-1; i++){
            //     ans2 = ans2 * 10 + y;
            // }
            // cout << ans2 << endl;

            //考虑比a小的
            int inni = a / pow(a, len);
            

        }



    }

    return 0;




}


int getlen(int a){

    if(a/10 == 0){
        return 1;
    }
    else{
        return 1 + getlen(a/10);
    }


}

