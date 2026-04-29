#include <iostream>
using namespace std;

#define int long long
int calc1(int x);

signed main(){

    int t;
    cin >> t;
    while(t--){
        int n, x;
        cin >> n >> x;
        int ans = 0;
        //计算从1开始的
        ans += calc1(n) - calc1(x);
        if((x-3) % 4 == 0){
            ans++;
        }
        ans %= 998244353;
        cout << "ans part 1 = " << ans << endl;

        //计算从偶数开始的

        int mol2is2, mol2is4;
        

        if(x % 2 == 1){
            if((x-1) % 4 == 2){
                mol2is2 = x / 4 + 1;
                mol2is4 = x / 4;
            }
            else{
                mol2is4 = x / 4;
                mol2is2 = x / 4;
            }
        }
        else{
            if(x % 4 == 2){
                mol2is2 = x / 4 + 1;
                mol2is4 = x / 4;
            }
            else{
                mol2is4 = x / 4;
                mol2is2 = x / 4;
            }
        }

        cout << "for " << x << " , %2==2 = " << mol2is2 << ", %2==4 = " << mol2is4 << endl;

        if(x % 2 == 0){
            x++;
        }
        if(n % 2 == 0){
            n--;
        }

        int mol2i2, mol2i4;
            if((n+1) % 4 == 2){
                mol2i2 = n / 4 + 1;
                mol2i4 = n / 4;
            }
            else{
                mol2i4 = n / 4;
                mol2i2 = n / 4;
            }

            if((x+1) % 4 == 2){
                mol2i2 -= x / 4 + 1;
                mol2i4 -= x / 4;
            }
            else{
                mol2i4 -= x / 4;
                mol2i2 -= x / 4;
            }

        

        cout << "for " << n << " , %2==2 = " << mol2i2 << ", %2==4 = " << mol2i4 << endl;
            ans %= 998244353;
        ans += mol2i2 * mol2is2 + mol2i4 * mol2is4;
        ans %= 998244353;
        cout << ans << endl;



    }


    return 0;

}


int calc1(int x){
    if(x < 3){
        return 1;
    }
    
    return (x-3)/4 + 2;

}