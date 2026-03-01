#include <iostream>
#include <algorithm>
using namespace std;

//建立在beautiful是要sum<10的。
//怎么wa了

int t;

int main(){

    cin >> t;
    for(int tt = 0; tt < t; tt++){
        string s;
        cin >> s;
        int len = s.length();

        if(len == 1){
            cout << "0" << endl;
            continue;
        }
        else{

            sort(s.begin()+1, s.end());
            int sum = 0;
            sum = s[0] - '0';
            int ans;
            
            //cout << s << endl;
            int index;
            for(index = 1; index < len; index++){
                sum += s[index] - '0';
                if(sum > 9){
                    ans = len - index;
                    break;
                }
                
            }
            if(index == len){
                ans = 0;
            }


            int sum2 = 0;
            sum2 = 1;
            int ans2 = 1;
            
            //cout << s << endl;
            
            for(index = 1; index < len; index++){
                sum2 += s[index] - '0';
                if(sum2 > 9){
                    ans2 += len - index;
                    //cout << "miao sum2 = " << sum2 << " index = " << index <<" ans2 = " << ans2 <<  endl;
                    break;
                }
            }

            ans = min(ans, ans2);
            cout << ans << endl;


        }

    }


    return 0;
}