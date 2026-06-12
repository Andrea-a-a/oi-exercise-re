#include <iostream>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(n % 2 == 0){
            for(int i = 1; i <= n/2; i++){
                int o = i * 2 - 1;
                int p = i * 2;
                cout << p << " " << o << " " << o << " " << p << " " << o << " " << p << " " << p << " " << o << " ";
            }
            cout << endl;
        }
        else{
            for(int i = 1; i <= n/2-1; i++){
                int o = i * 2 - 1;
                int p = i * 2;
                cout << p << " " << o << " " << o << " " << p << " " << o << " " << p << " " << p << " " << o << " ";
            }
            int a = n-2, b = n-1;
            cout <<a<<" "<<b<<" "<<n<<" "<<a<<" "<<b<<" "<<n<<" "<<n<<" "
            <<a<<" "<<b<<" "<<a<<" "<<b<<" "<<n<<endl;
        }
    }
    return 0;
}