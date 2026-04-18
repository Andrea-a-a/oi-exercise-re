#include <bits/stdc++.h>
using namespace std;

//输入格式为xx:xx:xx的字符串，输出秒数
int sto(string s){

    int u = ((s[0]-'0')*10 + s[1] - '0') * 60 * 60;
    u += ((s[3]-'0')*10 + s[4] - '0') * 60;
    u += ((s[6]-'0')*10 + s[7] - '0');

    return u;

}


int a[87000];


int main(){

    //差差的分
    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        string op, ed;
        cin >> op >> ed;
        //cout << sto(op) <<"++ed; " << sto(ed)+1 <<"--ed" << endl;
        a[sto(op)]++;
        a[sto(ed)+1]--;
    }

    int ans = 0;
    int now = 0;
    for(int i = 0; i < 86410; i++){
        now = now+a[i];
        ans = max(ans, now);
    }

    cout << ans;


    return 0;



}
