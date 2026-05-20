#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 3e5+10;
int cnt1[MAXN], cnt2[MAXN], cnt3[MAXN];

void inni();

int main(){


    //枚举分界点[0,len]，前面变全2后面变全13
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int len = s.length();
        int cnt4 = 0;

        //cnt[i] = 在[0,i]中有多少个
        inni();

        
        for(int i = 0; i < len; i++){
            if(s[i] == '4'){
                cnt4++;
            }
            if(i != 0){
                cnt1[i] = cnt1[i-1];
                cnt2[i] = cnt2[i-1];
                cnt3[i] = cnt3[i-1];
            }

            
            
            if(s[i] == '1'){
                cnt1[i]++;
            }
            else if(s[i] == '2'){
                cnt2[i]++;
            }
            else if(s[i] == '3'){
                cnt3[i]++;
            }

            //cout << "pt 1 i = " << i << endl;
            
        }

        int ans = len;

        for(int i = 0; i <= len; i++){
            int tmpans = 0;

            //前半段是index为[0, i-1]
            if(i != 0){
                tmpans += cnt1[i-1] + cnt3[i-1];
            }
            
            //后半段是index为[i, len-1]
            if(i != len){
                tmpans += cnt2[len-1] - cnt2[i-1];
            }

            ans = min(ans, cnt4+tmpans);

            //cout << "pt 2 i = " << i << endl;
        }

        cout << ans << endl;
        


    }


    return 0;

}


void inni(){
    memset(cnt1, 0, sizeof(cnt1));
    memset(cnt2, 0, sizeof(cnt2));
    memset(cnt3, 0, sizeof(cnt3));
}