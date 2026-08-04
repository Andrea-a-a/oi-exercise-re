#include <iostream>
#include <vector>
using namespace std;

int gcd(int a, int b){
    if(a > b){
        swap(a, b);
    }
    if(a == 0){
        return b;
    }

    return gcd(b % a, a);

}


int main(){
    //假设互质就是全对

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;

        int x, y;
        cin >> x >> y;
        if(x > y)   swap(x, y);
        int g = gcd(x, y);

        //cout << x << " " << y << " " << g << endl;

        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }

        if(g == 1){
            cout << "YES" << endl;
        }
        else{
            bool checker = 1;
            for(int i = 0; i < g; i++){
                int index = i;
                for(;index < n; index += g){
                    if(a[index] % g != (i+1) % g){
                        checker = 0;
                        break;
                    }
                }
            }
            checker ? cout << "YES" << endl : cout << "NO" << endl;
        }

    }

    return 0;
}