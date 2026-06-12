#include <iostream>
#include <cstring>

using namespace std;

bool ans[5100], a[5100];
int t, n, k;
string s;

int getlen(){
    int wait = 0, get = 0;
    for(int i = 0; i < n; i++){
        if(!a[i]){
            if(s[i] == '('){
                wait++;
            }
            else if(wait > 0){
                wait--;
                get++;
            }
        }
    }
    return get * 2;
}

int main(){

    cin >> t;
    while(t--){
        memset(ans, 0, sizeof(ans));
        memset(a, 0, sizeof(a));

        cin >> n >> k >> s;
        int len = s.length();

        int an = getlen();
        //cout << "inni ans = " << an << endl;

        for(int l = 0; l <= k; l++){
            memset(a, 0, sizeof(a));
            //cout << l << endl;

            int cntl = 0;
            int lindex;
            for(lindex = 0; lindex < len && cntl < l; lindex++){
                if(s[lindex] == '('){
                    cntl++;
                    a[lindex] = 1;
                }
            }

            int cntr = 0;
            for(int i = len-1; i >= lindex && cntr < k-l; i--){
                if(s[i] == ')'){
                    cntr++;
                    a[i] = 1;
                }
            }

            //cout << "current:" << getlen() << endl;

            if(an > getlen()){
                an = getlen();
                for(int i = 0; i < n; i++){
                    ans[i] = a[i];
                }
            }

            // for(int i = 0; i < n; i++){
            //     cout << a[i]; 
            // }
            // cout << " meow";



        }

        for(int i = 0; i < len; i++){
            cout << ans[i];
        }
        cout << endl;
        //cout << " " << an << endl;



    }




    return 0;
}