#include <bits/stdc++.h>
using namespace std;

long long h[1010][1010];

//遮住x面，第x种方式
int pl[7][2];

// void ini(){
//     memset(h, 0, sizeof(h));
    
    
// }

void solve(){
    // ini();


    
    int n, m;
    cin >> n >> m;
    long long ans = 0;

    for (int j = 1; j <= m; ++j) {
        h[0][j] = 0;
        h[n + 1][j] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        h[i][0] = 0;
        h[i][m + 1] = 0;
    }
    h[0][0] = h[0][m + 1] = h[n + 1][0] = h[n + 1][m + 1] = 0;


    for(int i = 1; i <= n; i++){
        for(int o = 1; o <= m; o++){
            cin >> h[i][o];
        }
    }

    for(int i = 1; i <= n; i++){
        for(int o = 1; o <= m; o++){
            //处理h[i][o]
            if(h[i][o] == 0)    continue;
            else if(h[i][o] == 1){
                int cnt = 0;
                if(h[i+1][o] >= 1)  cnt++;
                if(h[i-1][o] >= 1)  cnt++;
                if(h[i][o+1] >= 1)  cnt++;
                if(h[i][o-1] >= 1)  cnt++;

                //cout << "  " << cnt << endl;

                int ad = 0;

                if(cnt == 0)    ad = 21;
                else if(cnt == 1)   ad = pl[1][0];
                else if(cnt == 3) ad = pl[3][0];
                else if(cnt == 4)   ad = 7;
                else if(cnt == 2){
                    if((h[i-1][o] >= h[i][o] && h[i+1][o] >= h[i][o]) || (h[i][o+1] >= h[i][o] && h[i][o-1] >= h[i][o])){
                        ad = pl[2][0];
                    }
                    else{
                        ad = pl[2][1];
                    }
                }
                //cout << "added: " << ad << endl;
                ans += ad;
                continue;
            }

            //cout << "i: " << i << "o: " << o << " ans1: " << ans << endl; 

            long long h1[4];
            h1[0] = h[i+1][o], h1[1] = h[i-1][o], h1[2] = h[i][o+1], h1[3] = h[i][o-1];

            int topcnt = 0, btmcnt = 0;
            
            for(int w = 0; w < 4; w++){
                if(h1[w] >= h[i][o])    topcnt++;
                if(h1[w] >= 1)  btmcnt++;
                h1[w] = min(h1[w], h[i][o] - 1);
                h1[w] = max(h1[w], 1ll);
            }
            sort(h1, h1+4);

            // for(int w = 0; w < 4; w++){
            //     cout << h1[w] << endl;
            // }
            //cout << "topcnt " << topcnt << " btmcnt " << btmcnt << endl;

            //有h1[0]个被遮住四个侧面，即全都不露出来, 不用加
            //h1[0] + 1 到h1[1]被遮住3个侧面，即被遮住五个侧面
            ans += (h1[1] - h1[0]) * pl[5][0];
            //h1[1] + 1 到h1[2]被遮住2个侧面，讨论一下它们的位置
            //是面对面的
            if((h1[1] + 1 <= h[i+1][o] && h1[1] + 1 <= h[i-1][o]) 
                || (h1[1] + 1 <= h[i][o+1]  && h1[1] + 1 <= h[i][o-1])){
                    ans += (h1[2] - h1[1]) * pl[4][0];
                }
                //不是面对面的
            else{
                ans += (h1[2] - h1[1]) * pl[4][1];
            }
            //h1[2]+1 到h1[3]被遮住一个侧面
            ans += (h1[3] - h1[2]) * pl[3][0];

            //遮住0个侧面
            ans += (h[i][o] - 1 - h1[3]) * pl[2][0];

            //cout << "i: " << i << "o: " << o << " ans1: " << ans << endl; 
                //单独考虑底下的
                if(btmcnt == 0){
                    ans += pl[1][0];
                }
                else if(btmcnt == 1){
                    ans += pl[2][1];
                }
                else if(btmcnt == 3){
                    ans += pl[4][1];
                }
                else if(btmcnt == 4){
                    ans += 6;
                }
                else if(btmcnt == 2){
                    if((h[i-1][o] >= 1 && h[i+1][o] >= 1) || (h[i][o+1] >= 1 && h[i][o-1] >= 1)){
                        ans += pl[3][0];
                    }
                    else{
                        ans += pl[3][1];
                    }
                }
               // cout << "i: " << i << "o: " << o << " ans1: " << ans << endl; 

                //单独考虑顶上的
                if(topcnt == 0){
                    ans += pl[1][0];
                }
                else if(topcnt == 1){
                    ans += pl[2][1];
                }
                else if(topcnt == 3){
                    ans += pl[4][1];
                }
                else if(topcnt == 4){
                    ans += 6;
                }
                else if(topcnt == 2){
                    if((h[i-1][o] >= h[i][o] && h[i+1][o] >= h[i][o]) || (h[i][o+1] >= h[i][o] && h[i][o-1] >= h[i][o])){
                        ans += pl[3][0];
                    }
                    else{
                        ans += pl[3][1];
                    }
                }
            
  

           // cout << "i: " << i << "o: " << o << " ans2: " << ans << endl; 


        }
    }

    cout << ans << endl;
    


}



int main(){

    pl[0][0] = 21;
    pl[0][1] = 21;
    pl[6][1] = 0;
    pl[6][0] = 0;
    pl[5][0] = 6;
    pl[5][1] = 6;
    pl[4][0] = 7;
    pl[4][1] = 11;
    pl[3][0] = 13;
    pl[3][1] = 15;
    pl[2][0] = 14;
    pl[2][1] = 18;
    pl[1][0] = 20;
    pl[1][1] = 20;

    

    int t;
    cin >> t;
    while(t--){
        solve();
    }


    return 0;
}