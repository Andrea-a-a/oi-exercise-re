#include <iostream>
#include <math.h>
using namespace std;

#define int long long

int getlen(int a);
int ten[20];

int getmin(int inni, int len, int x, int y);
int getmax(int inni, int len, int x, int y);


signed main(){

    //cout << getlen(1999) << endl;

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
        //cout << getlen(a) << endl;

        //if(len == 1){
        //    cout << min(abs(a-x), abs(a-y)) << endl;
        //}
        //else{

            //先求出前缀！
            int tmp = a;
            int pre = 0, prelen = 0;
            for(int i = len-1; i >= 0; i--){
                if((a/ten[i])%10 == x || a/ten[i]%10 == y){
                    pre += ((a/ten[i])%10) * ten[i];
                    prelen++;
                    //cout << "  i = " << i <<  endl;
                }
                else{
                    break;
                }
            }
            if(prelen == len){
                cout << "0" << endl;
                continue;
            }

            //cout << "pre = " << pre << "prelen = " << prelen <<endl;

            //求出比它小的数中的最大的
            int ansmin = 0;

            //如果prelen = 0
            // if(prelen == 0){
            //     //说明第一位不能对上
                
            // }

            ansmin = pre + getmin((a/ten[len-1-prelen])%10, len-prelen, x, y);

            //cout << "ansmin = " << ansmin << endl;


            //求出比它大的数中最小的
            //先求长度为len+1的
            int ansmax = 0;
            if(x == 0){
                ansmax = y * ten[len];
            }
            else{
                for(int i = 0; i <= len; i++){
                    ansmax += x * ten[i];
                }
            }

            //然后求长度为len的
            int ansmax2 = 0;
            int fst = (a/ten[len-1-prelen])%10;
            //如果fst比y还大，则不存在长度为len的可行值，并且fst不会是x或y
            if(fst < y){
                ansmax2 = pre + getmax(fst, len-prelen, x, y);
            }

            //cout << "ansmax = " << ansmax << " or " << ansmax2 << endl;

            int ans = abs(a - ansmin);
            if(ansmax != 0){
                ans = min(abs(ansmax-a), ans);
            }
            if(ansmax2 != 0 && ansmax2 != -1){
                ans = min(abs(ansmax2 - a), ans);
            }

            cout << ans << endl;
        //}



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

int getmin(int inni, int len, int x, int y){
    int ansmin = 0;
    if(x == 0){
                        if(inni > y){
                            for(int i = 0; i <= len-1; i++){
                                ansmin += y*ten[i];
                            }
                        }
                        else{
                            for(int i = 0; i <= len-2; i++){
                                ansmin += y*ten[i];
                            }
                        }
                    }
    else if(inni > y){
                        //第一位比大数大
                        for(int i = 0; i <= len-1; i++){
                            ansmin += y*ten[i];
                        }
                    }
                    else if(inni < y && inni > x){
                        //第一位在中间
                        for(int i = 0; i <= len-1; i++){
                            ansmin += x*ten[i];
                        }
                    }
                    else{
                        //第一位比小数小
                        for(int i = 0; i <= len-2; i++){
                            ansmin += y * ten[i];
                        }
                    }

    return ansmin;
}

int getmax(int inni, int len, int x, int y){
    if(inni > y){
        return -1;
    }
    else{
        int rtn = 0;
        if(inni < x){
            for(int i = 0; i <= len-1; i++){
                rtn += x * ten[i];
            }
        }
        else{
            for(int i = 0; i <= len-1; i++){
                rtn += y * ten[i];
            }
        }
        return rtn;
    }
}