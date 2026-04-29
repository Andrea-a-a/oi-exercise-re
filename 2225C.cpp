#include <iostream>
using namespace std;

int t;
void aut(int n);


int main(){
    cin >> t;
    while(t--){
        int tmp;
        cin >> tmp;
        aut(tmp);
    }



}

void aut(int n){
    char a[2][200010];
    for(int i = 1; i <= n; i++){
        cin >> a[0][i];
    }
    for(int i = 1; i <= n; i++){
        cin >> a[1][i];
    }

    int ans = 0;
    for(int i = 1; i <= n; i++){
        if(a[0][i] == a[1][i]){
            continue;
        }
        else{
            if(i == n){
                ans++;
            }
            else{
                
                if(a[0][i] == a[0][i+1] && a[1][i] == a[1][i+1]){
                    i++;
                    continue;
                }
                else if(a[0][i] != a[0][i+1] && a[1][i] != a[1][i+1]){
                    if(i+2 <= n){
                        if(a[1][i+1]==a[1][i+2] && a[0][i+1] == a[0][i+2]){
                            ans++;
                            i += 2;
                            continue;
                        }
                    }
                    i++;
                    ans+= 2;

                }
                else{
                    i++;
                    ans++;
                    
                }
                
            }
        }
    }
    cout << ans << endl;


}