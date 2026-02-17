#include <bits/stdc++.h>
using namespace std;

int t;

int main(){
    cin >> t;
    for(int i = 0; i < t; i++){
        int n;
        cin >> n;

        stack<unsigned long long> s;


        for(int o = 0; o < n; o++){
            string opt;
            cin >> opt;
            if(opt == "push"){
                unsigned long long w;
                cin >> w;
                s.push(w);
            }
            else if(opt == "pop"){
                if(s.empty()) cout << "Empty" << endl;
                else    s.pop();
            }
            else if(opt == "query"){
                if(s.empty())   cout << "Anguei!" << endl;
                else cout << s.top() << endl;
            }
            else if(opt == "size"){
                cout << s.size() << endl;
            }




        }




    }


    return 0;
}