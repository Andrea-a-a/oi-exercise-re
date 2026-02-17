#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, l;
int a[210][210];
int chafen[65540];

bool csp[5][9]={
    {1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,1,0,1},
    {1,0,0,1,1,1,1,1,0},
    {1,0,0,0,0,1,1,0,0},
    {1,1,1,1,1,1,1,0,0}
};

void zairu(int x, int y){
    //(x,y]是合法的
    chafen[x+1]++;
    chafen[y+1]--;
}


signed main(){
    cin >> n >> l;
    for(int i = 1; i <= n; i++){
        for(int o = 1; o <= n; o++){
            cin >> a[i][o];
        }
    }
    for(int x = 1; x <= n-4; x++){
        for(int y = 1; y <= n - 8; y++){
            //在黑黑的块里面取最大值
            int minn = -1e5;
            //在白白的块里面取最小值
            int maxx = 1e9;

            //k取(minn, maxx]

            for(int i = 0; i < 5; i++){
                for(int o = 0 ; o < 9; o++){
                    if(!csp[i][o]){
                        //说明是黑黑的
                        minn = max(minn, a[x+i][y+o]);
                    }
                    else{
                        maxx = min(maxx, a[x+i][y+o]);
                    }

                }
            }

            if(minn < maxx){
                //cout << "x = " << x <<  " y = " << y << " 载入了" << minn << "和"  << maxx << endl;
                zairu(minn, maxx);
            }
        }
    }

    //前缀和。
    int sum = 0;
    for(int k = 1; k <= l-1; k++){
        sum+=chafen[k];
        if(sum > 0) cout << k << endl;
    }



}