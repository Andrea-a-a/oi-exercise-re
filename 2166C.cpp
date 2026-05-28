#include <iostream>
#include <cstring>
using namespace std;
long long a[200010];



int main(){

    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        memset(a, 0, sizeof(a));

        int n;
        cin >> n;
        long long maxa = -1;
        for(int o = 0; o < n; o++){
            cin >> a[o];
            maxa = max(maxa, a[o]);
        }
        maxa = -maxa;


            for(int w = 0; w < n; w++){

                
                int q = (w+1)%n;
                maxa += max(a[w], a[q]);
                

            }


        cout << maxa << endl;
    }



    return 0;
}

