#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

long long base[32];

// int getlen(long long x){
//     for(int i = 0; i <= 30; i++){
//         if(x >= base[i] && x <= base[i+1] -1){
//             return i;
//         }
//     }
//     return -1;
// }

string getbs(long long x){
    string s = "";
    while(x > 0){
        if(x % 2 == 0){
            s += '0';
        }
        else{
            s += '1';
        }
        x = x >> 1;
    }
    reverse(s.begin(), s.end());
    return s;
}

void solve(){
    int n;
    
    long long l, r;
    cin >> l >> r; cin >> n;
    int lenl, lenr;

    string strl = getbs(l), strr = getbs(r);
    //cout << "stage1: " << strl << " " << strr<< endl;

    lenl = strl.length(), lenr = strr.length();
    if(lenr == lenl){
        int index = 0;
        for(;index < lenr; index++){
            if(strr[index] != strl[index])  break;
        }
        strr[index] = '1';
        for(int i = index+1; i <= lenl - 1; i++){
            strr[i] = '0';
        }
    }
    else if(lenr - lenl == 1){
        strr = "1";
        for(int i = 1; i < lenr; i++){
            strr += '0';
        }
    }
    else if(lenr - lenl > 1){
        strr = "1";
        for(int i = 1; i < lenr; i++){
            strr += '0';
        }
        strl = "1";
        for(int i = 1; i < lenr - 1; i++){
            strl += '0';
        }
    }

    lenl = strl.length();
    lenr = strr.length();

    //cout << "stage2: " << strl << " " << strr << endl;


    int cnt = 0;
    while(cnt < n){
            if(strl[cnt%lenl] == '1' && strr[cnt%lenr] == '1'){
                cout << "1";
            }
            else{
                cout << "0";
            }

            cnt++;
            
    }
       cout << endl;


}

int main(){

    base[0] = 1;
    for(int i = 1; i <=30 ; i++){
        base[i] = base[i-1] * 2;
    }

    int t;
    cin >> t;
    while(t--){
        solve();
        // int x;
        // cin >> x;
        // cout << getbs(x) << endl;
    }

    return 0;
}