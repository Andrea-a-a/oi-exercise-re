#include <iostream>
using namespace std;
int n;

int main(){
    cin >> n;
    

    for(int i = 0; i < n; i++){
        int m;
        cin >> m;
        
        int nump, numn, num0;
        
        num0 = nump = numn = 0;


        for(int o = 0; o < m; o++){
            int temp;
            cin >> temp;
            if(temp == 0)   num0++;
            else if(temp == -1) numn++;
            else if(temp == 1)  nump++;


        }
        int ans=num0;
        if(numn % 2 != 0)   ans = ans+2;

        //cout << '~' << ans << '~' << endl;
        cout << ans << endl;

    }



    return 0;
}