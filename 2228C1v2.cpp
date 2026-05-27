#include <iostream>
#include <math.h>
using namespace std;

#define int long long

int getlen(int a);
int ten[20];
int dig(int a, int pow);


signed main(){

    ten[0] = 1;
    for(int i = 1; i <= 18; i++){
        ten[i] = ten[i-1]*10;
    }

    //cout << ten[19];

    int t;
    cin >> t;
    while(t--){

        int a, n, x, y;
        cin >> a >> n >> x >> y;

        if(x > y){
            swap(x, y);
        }

        int len = getlen(a);
    
        int ans = 0;

        //如果刚好可以相等的话……
        bool equal = 1;
        for(int i = len-1; i >= 0; i--){
            if(dig(a, i) != x && dig(a, i) != y){
                equal = 0;
                break;
            } 
        }

        if(equal){
            cout << "0" << endl;
            continue;
        }

        if(len == 1 && a < x){
            cout << x-a << endl;
            continue;
        }

        //来考虑比a大的
        int greater = 0;
        for(int i = len-1; i >= 0; i--){
            int tmp = dig(a, i);
            if(tmp != x && tmp != y){
                
                if(tmp < y){
                    if(tmp < x){
                        greater += x * ten[i];
                    }
                    else{
                        greater += y * ten[i];
                    }

                    for(int o = i-1; o >= 0; o--){
                        greater += x * ten[o];
                        //cout << "meow0" << endl;
                    }
                    break;
                }
                else{
                    //cout << "rolling back... i = " << i << endl;
                    int o;
                    bool Failed = 1;
                    for(o = i+1; o < len; o++){
                        int digo = dig(a, o);
                        greater -= digo * ten[o];

                        //cout << "o = " << o << " greater = " << greater << endl;
                        
                        
                        if(digo < y){
                            Failed = 0;
                            (digo < x) ? greater += x * ten[o] : greater += y * ten[o];
                            
                            // greater = greater / ten[o];
                            // greater *= ten[o];

                            for(int p = o-1; p >= 0; p--){
                                greater += x * ten[p];
                                //cout << "greater = " << greater << endl;
                            }
                            i = -1;
                            break;
                        }

                    }
                    if(o == len){
                        // if(Failed){
                        //     greater = 0;
                        //     if(x != 0){
                        //         for(int w = 0; w <= len; w++){
                        //             greater += x * ten[w];
                        //         }
                        //     }
                        //     else{
                        //         for(int w = 0; w <= len; w++){
                        //             greater += y * ten[w];
                        //         }
                        //     }

                        // // }
                        // else{
                            greater = 0;
                            if(x != 0){
                                for(int w = 0; w <= len; w++){
                                    greater += x * ten[w];
                                }
                            }
                            else{
                                greater = y * ten[len];
                            }
                            //(x != 0) ? greater = x * ten[len] : greater = y * ten[len];
                        // }
                        break;
                    }

                    
                }
            }
            else{
                greater += tmp * ten[i];
            }

            //cout << "i = " << i << " greater = " << greater << endl;
        }


        //来考虑比a小的
        int less = 0;
        for(int i = len-1; i >= 0; i--){
            int digi = dig(a, i);
            if(digi != x && digi != y){
                if(digi > x){

                    (digi > y) ? less += y * ten[i] : less += x * ten[i];

                    for(int p = i-1; p >= 0; p--){
                        less += y * ten[p];
                    }
                    break;
                }
                else{
                    // bool Failed = 1;
                    //cout << "rolling back... i = " << i << endl;
                    int o;
                    for(o = i+1; o < len; o++){
                        int digo = dig(a, o);
                        less -= digo * ten[o];

                        if(digo > x){
                            // Failed = 0;

                            (digo > y) ? less += y * ten[o] : less += x * ten[o];
                        
                            for(int p = o-1; p >= 0; p--){
                                less += y * ten[p];
                            }
                            i = -1;
                            break;
                        }

                    }
                    if(o == len){

                        for(int p = 0; p <= len-2; p++){
                                less += y * ten[p];
                        }
                    }
                    break;
                }
            }
            else{
                less += digi * ten[i];
            }
        }
        
        cout << min(abs(a - less), abs(a - greater));
        cout << endl;
        //cout << "  greater = " << greater << " less = " << less <<endl;
        //cout << "2 greater = " << greater << endl;

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

int dig(int a, int pow){
    return (a/ten[pow])%10;
}