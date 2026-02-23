#include <iostream>
#include <cstring>
using namespace std;

int t;
const int MAXN = 2e5+10;
long long a[MAXN];
long long psum[MAXN];
//pmin[o] : [1, o]
long long pmin[MAXN];
//smax[o] : [o, n]
long long smax[MAXN];

void inni(void);

int main(){

    ios::sync_with_stdio(0);

    cin >> t;
    for(int w = 0; w < t; w++){
        inni();
        int n;
        long long h, k;
        cin >> n >> h >> k;
        long long sum = 0;

        for(int i = 1; i <= n; i++){
            cin >> a[i];
            sum += a[i];
            psum[i] = sum;
            
        }

        pmin[1] = a[1];
        for(int i = 2; i <= n; i++){
            pmin[i] = min(pmin[i-1], a[i]);
            //cout << "pmin[" << i  << "] = " << pmin[i] << endl; 
        }

        smax[n] = a[n];
        for(int i = n-1; i >= 1; i--){
            smax[i] = max(smax[i+1], a[i]);
           // cout << "smax[" << i  << "] = " << smax[i] << endl; 
        }


        long long ans = 0;
        if(h % sum > 0){
            ans = (h/sum) * (n+k);
        }
        else{
            ans = (h/sum - 1) * (n + k) + n;
            cout << ans << endl;
            
            continue;
        }

        h = h % sum;
        
        long long ans2 = 0;
        for(int i = 1; i <= n; i++){
            if(psum[i] >= h){
                ans2 = i; 
                break;
            }
            if(psum[i] - pmin[i] + smax[i+1] >= h){
                ans2 = i;
                break;
            }
        }

        cout << ans + ans2 << endl;


        //现在在一轮内肯定能杀死敌人了。而且h是<sum的。
        




        /*
         哇塞t了

        //计算以现在的情况要多久才能杀死敌人
        long long ans2 = 0;
        long long temp = 0;
        for(int i = 1; i <= n; i++){
            temp += a[i];
            ans2++;
            if(temp >= h){
                break;
            }
        }

        //需要ans2个子弹。
        //寻找[ans2 , n]中的最大值
        long long maxA = 0;
        for(long long i = ans2; i <= n; i++){
            maxA = max(maxA, a[i]);
        }
        
        //使用它和[1, ans2-1]交换
        for(int i = 1; i < ans2; i++){
            if(a[i] > maxA){
                continue;
            }
            long long ans3 = 0;
            long long temp2 = 0;
            swap(a[i], maxA);
            for(int o = 1; o <= n; o++){
                temp2 += a[o];
                ans3++;
                if(temp2 >= h){
                    break;
                }
            }
            ans2 = min(ans2, ans3);
            swap(a[i], maxA);
        }

        

        */




    }


    return 0;
}

void inni(){

    memset(a, 0, sizeof(a));


}