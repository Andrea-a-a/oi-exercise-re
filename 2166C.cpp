#include <iostream>
#include <cstring>
using namespace std;
long long a[200010];
bool merged[200010];


int main(){

    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        memset(a, 0, sizeof(a));
        memset(merged, 0, sizeof(merged));
        int n;
        cin >> n;
        for(int o = 0; o < n; o++){
            cin >> a[o];
        }
        int ans = 0;
        for(int o = 0; o < n-1; o++){
            long long temp = 1e10;
            int index = 2e5+10;
            int index2 = 2e5+10;
            
            for(int w = 0; w < n; w++){
                int p = w;
                while(merged[p])    p = (p+1)%n;
                int q = (p+1)%n;
                while(merged[q])    q = (q+1)%n;
                if(temp > max(a[p], a[q])){
                    temp = max(a[p], a[q]);
                    index = p;
                    index2 = q;
                }

            }
                if(a[index] > a[index2])    merged[index2] = 1;
                else    merged[index] = 1;
                ans += temp;
            //cout << "     temp: " << temp << "    merge " <<  index << " and " << index2<< endl;
        }
        cout << ans << endl;
    }



    return 0;
}

