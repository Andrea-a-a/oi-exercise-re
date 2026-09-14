#include <bits/stdc++.h>
using namespace std;

bool ac[420][14];
int accnt[420];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int a, b, c;
        cin >> a >> b >> c;
        if(c < 240){
            if(!ac[a][b]){
                ac[a][b] = true;
                accnt[a]++;
                cout << b << '\n';
            }
            else{
                cout << "0\n";
            }
        }
        else{
            if(!ac[a][b]){
                if(accnt[a] < 3){
                    cout << b << '\n';
                }
                else{
                    cout << "0\n";
                }
                ac[a][b] = true;
                accnt[a]++;
            }
            else{
                cout << "0\n";
            }
        }
    }
    


    return 0;
}