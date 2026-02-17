#include <bits/stdc++.h>
using namespace std;


int main(){
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < k; i++){
        int x, y;
        cin >> x >> y;
        string s;
        cin >> s;
        int len = s.length();
        for(int o = 0; o < len; o++){
            if(s[o] == 'f'&& y+1<=n)         y++;
            else if(s[o] == 'b' && y-1 >= 1)    y--;
            else if(s[o] == 'l' && x-1 >= 1)    x--;
            else if(s[o] == 'r' && x+1 <= n)    x++;
        }
        cout << x << " " << y << endl;
    }
    return 0;
}