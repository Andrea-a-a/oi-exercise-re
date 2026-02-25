#include <iostream>
#include <cstring>
#include <map>
using namespace std;

int t;
const int MAXN = 3e5 + 10;
long long a[MAXN];

//isCanceled
bool b[MAXN];


void init();


int main(){

    cin >> t;
    for(int e = 0; e < t; e++){
        init();
        int n;

        cin >> n;

        for(int i = 1; i <= n; i++){
            cin >> a[i];
        }

        /*
        int ans = n;
        for(int i = n; i >= 2; i--){
            //从后面开始扫
            if(a[i] - a[i-1] == 1){
                //cancel a[i]
                b[i] = 1;
                ans--;
                for(int o = i+1; o <= n; o++){
                    //如果b[o]已经被cancel了
                    if(b[o]){
                        continue;
                    }

                    if(a[i] == a[o]){
                        //cancel a[o]
                        b[o] = 1;
                        ans--;
                    }
                    else{
                        break;
                    }
                }
            }


        }

        cout << ans << endl;
        */

    map<int,int> s;
    int block = 0, count = 0;
    for(int i = 1; i<=n; i++){
        s[a[i]]=i;
        int lst = 0;
        if(s.find(a[i]-1)!=s.end()){
            lst=s[a[i]-1];
        }
        if(lst==0||lst<block){
            block=i;
            count++;
        }




    }
    cout << count << endl;
}





}

void init(){
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));



}