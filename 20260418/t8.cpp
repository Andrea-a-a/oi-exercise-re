#include <bits/stdc++.h>
using namespace std;

int n;
string s;

void opt1(string w){
    //int cnt = 0;
    if(s.find(w) != string::npos){
        int ans1 = s.find(w);
        cout << ans1;
        if(s.substr(ans1+1, s.size() - ans1 -1).find(w) != string::npos){
            int ans2 = s.substr(ans1+1, s.size() - ans1 -1).find(w);
            cout << " " << ans2 + ans1+1;

            if(s.substr(ans1+ans2+2, s.size() - ans1-ans2 -2).find(w) != string::npos){
                    int ans3 = s.substr(ans1+ans2+2, s.size() - ans1-ans2 -2).find(w);

                cout << " " << ans3+ans2+ans1+2;
            }
        }
        cout << endl;
    }
    else{
        cout << "-1" << endl;
    }
}



int main(){

    cin >> n >>s;
    while(n--){
        int opt;
        cin >> opt;
        if(opt == 1){
            string s1;
            cin >> s1;
            opt1(s1);
        }
        else if(opt == 2){
            int index;
            string s2;
            cin >> index >> s2;
            if(index != s.size()){
                s.insert(index, s2);
            }
            else{
                s += s2;
            }
            cout << s <<endl;
        }
        else if(opt == 3){
            int l, r;
            cin >> l >> r;
            string tmp = "";
            for(int q = r; q >= l; q--){
                tmp+=s[q];
            }
            s.replace(l, r-l+1, tmp);
            cout << s << endl;
        }
    }



    return 0;
}
