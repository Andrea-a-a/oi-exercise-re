#include <iostream>
#include <math.h>
using namespace std;

#define int long long

int getlen(int a);
int ten[20];


signed main(){

    ten[0] = 1;
    for(int i = 1; i <= 19; i++){
        ten[i] = ten[i-1]*10;
    }

    int t;
    cin >> t;
    while(t--){

        int a, n, x, y;
        cin >> a >> n >> x >> y;

        if(x > y){
            swap(x, y);
        }

        int len = getlen(a);
    

        
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
