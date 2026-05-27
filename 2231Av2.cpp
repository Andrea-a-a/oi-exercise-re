#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 510;

int t;
int n;


int main(){
    cin >> t;
    while(t--){

        cin >> n;
        

        
        for(int i = 1; i <= n; i++){
            cout << n + i << " ";
        }

        cout << endl;
        
    }


    return 0;
}