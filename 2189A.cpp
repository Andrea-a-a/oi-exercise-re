#include <iostream>
using namespace std;

int t;


int main(void){
    cin >> t;
    for(int i = 0; i < t; i++){
        int n, h, l;
        cin >> n >> h >> l;
        //int a[100];
        int minh = min(h, l);
        int maxh = max(h, l);
        int goodgood = 0;
        int largerthanmax = 0;
        for(int i = 0; i < n; i++){
            int temp;
            cin >> temp;
            if(temp > minh  && temp <= maxh){
                largerthanmax++;
            }
            else if(temp >= 0 && temp <= minh){
                goodgood++;
            }
        }
       // cout << "   goodgood:" << goodgood << "   largerthanmax:" << largerthanmax << endl;

        if(largerthanmax > goodgood){
            cout << goodgood << endl;
        }
        else{
            cout << largerthanmax + (goodgood-largerthanmax)/2 << endl;
        }

    }
    
    return 0;


}
