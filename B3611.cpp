#include <iostream>
#include <math.h>

using namespace std;

int a[110][110], b[110][110];
int n;

int main(){

    cin >> n;
    for(int i = 1; i <= n; i++){
        for(int o = 1; o <= n; o++){
            cin >> b[i][o];
        }
        //a[i][i] = 1;
    }
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            //if(k == i)  continue;
            for(int j = 1; j <= n; j++){
                //if(k == j)  continue;
                b[i][j] = max(b[i][j], min(b[i][k], b[k][j]));
            }
        }
    }

    for(int i = 1; i <= n; i++){
        for(int o = 1; o <= n; o++){
            cout << b[i][o] << " ";
        }
        cout << endl;
    }


}