#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 510;
bool used[2 * MAXN];
int t;
int n;

void inni(){
    memset(used, 0, sizeof(used));
    n = 0;
}

int main(){
    cin >> t;
    while(t--){
        inni();
        cin >> n;
        

        cout << "1 ";
        used[1] = 1;
        int index = 1;
        int priv = 1;
        for(int i = 1; i < n; i++){
            while(used[index])
            {
                index++;
            }
            cout << index << " ";
            used[index] = 1;
            used[index + priv] = 1;
            priv = index;
        }

        cout << endl;
        
    }


    return 0;
}