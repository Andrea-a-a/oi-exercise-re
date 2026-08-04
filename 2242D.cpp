#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int solve(){
    string a, b;
    cin >> a >> b;
    string suma = "", sumb = "";
    int lena = a.length(), lenb = b.length();
    suma += a[0];
    for(int i = 1; i < lena; i++){
        suma += (a[i] + suma[i-1] - '0' - '0') % 10 + '0';
    }
    sumb += b[0];
    for(int i = 1; i < lenb; i++){
        sumb += (b[i] + sumb[i-1] - '0' - '0') % 10 + '0';
    }

    if(suma[lena-1] != sumb[lenb - 1])  return -1;
    int dp[lena+1][lenb+1];
    //dp[0][0] = 0, dp[0][1] = 0, dp[1][0] = 0;
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= lena; i++){
        for(int o = 1; o <= lenb; o++){
            
            if(suma[i-1] == sumb[o-1]){
                dp[i][o] = dp[i-1][o-1] + 1;
                //cout << "i: " << i << "o: " << o << endl;
            }
            else{
                dp[i][o] = max(dp[i][o-1], dp[i-1][o]);
            }
            //cout << dp[i][o] << endl;
        }
    }

    return dp[lena][lenb];
    //cout << suma << endl << sumb << endl;
    //cout << dp[lena][lenb] << endl;
    
}

int main(){
    int t;
    cin >> t;
    while(t--){
        cout << solve() << endl;
    }
    return 0;
}