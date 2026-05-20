#include <iostream>
using namespace std;


int main(){


    //首先不能有4
    //其次2前面不能有1也不能有3
    //1后面不能有2
    //3后面不能有2
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int len = s.length();
        int cnt4 = 0, cntmth1 = 0, cntmth2 = 0;
        bool begin1 = 0, begin2 = 0, begin3 = 0;
        for(int i = 0; i < len; i++){
            if(s[i] == '4'){
                cnt4++;
            }
            else if(s[i] == '1' && begin1 == 0){
                begin1 = 1;
            }
            else if(s[i] == '3' && begin3 == 0){
                begin3 = 1;
            }
            else if((begin1 || begin3) && s[i] =='2'){
                cntmth1++;
            }

            
        }

        for(int i = len - 1; i >= 0; i--){
            if(s[i] == '2' && begin2 == 0){
                begin2 = 1;
            }
            else if((s[i] == '1' || s[i] == '3') && begin2){
                cntmth2++;
            }
        }
        // cout << "method1 " << cntmth1 << "  method2 = ";
        // cout << cntmth2 << endl;

        cout << cnt4 + min(cntmth1, cntmth2) << endl;


    }


    return 0;




}