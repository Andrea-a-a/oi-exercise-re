#include <bits/stdc++.h>
using namespace std;

#define int unsigned long long

int n, a, b;
unsigned long long ten[17];// = {1, 10, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11, 1e12, 1e13, 1e14, 1e15};

signed main(){

    cin >> n >> a >> b;
   

    ten[0] = 1;
    
    int tmp = 1;
    for(int i = 1; i < 16; i++){
        ten[i] =10 * ten[i-1];
        //cout << ten[i] << endl;
    }

    a = max(ten[n-1], a);


    //cout << a << "    ";
    for(int i = a; i <= b;i++){
        
        /*
        //一位一位check？
        for(int o = 2; o <= n; o++){
            if((i / pow(10,n-o))%o != 0){
                i += pow(10, n-o);
            }

        }
        */

        //先写暴力
        for(int o = n-2; o >= 0; o--){
            cout << "o = " << o <<",对于前" << n-o << "位, " << i << "/" << ten[o]  << endl;


            if((i / ten[o]) % (n-o) != 0){
                break;
            }



        }
        cout << i << endl;


    }




    return 0;
}

/*

    从左到右数的第2/4/6/8/etc偶数位一定是偶数；第5/15/etc位是5或0；第10/20/etc位是0。




*/