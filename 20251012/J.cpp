#include <bits/stdc++.h>
using namespace std;

int t;
int a[10010];
int oprl[10010];
int oprr[10010];

int main(){
    cin >> t;
    for(int i = 0; i < t; i++){
        memset(a, 0, sizeof(a));
        memset(oprl, 0, sizeof(oprl));
        memset(oprr, 0, sizeof(oprr));

        int n;
        cin >> n;
        for(int o = 1; o <= n; o++){
            cin >> a[o];
        }

        int l = 1;
        int r = n;

        int k = 0;
        while(a[l] == l && l <= n) l++;
        while(l < r){
            int tempr = r;
            if(a[l] > a[r]){
                k++;
                oprl[k] = l;
                oprr[k] = r;
                break;
            }
            
            while(a[l] < a[tempr])  tempr--;
            
            k++;
            oprl[k] = l;
            oprr[k] = tempr;
            sort(a+l, a+tempr+1);
            while(a[l] == l && l <= n) l++;
        }

        cout << k << endl;
        //cout << "            " << k << endl;
        for(int i = 1; i <= k; i++){
            //cout << "           " << oprl[k] << "  " << oprr[k] << endl;
            cout << oprl[i] << " " << oprr[i] << endl;
        }


    }

    


    return 0;
}