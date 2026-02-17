#include <bits/stdc++.h>
using namespace std;

int t;
string assign(string s);

int main(){

    cin >> t;
    for(int i = 0; i < t; i++){
        string s;
        cin >> s;
        cout << "        " << assign(s) << endl;
    }

    return 0;
}

/*
string assign2(string s){
    string ans = s;
    for(int i = 0; i < s.length()/2; i++){
        if(s[i] == '(' || s[i] == ')'){
            ans[i] = '(';
        }
        else{
            ans[i] = '[';
        }
    }
    for(int i = s.length()/2; i < s.length(); i++){
        if(s[i] == '(' || s[i] == ')'){
            ans[i] = ')';
        }
        else{
            ans[i] = ']';
        }
    }
    return ans;

}
    */


string assign(string s){

    int rndL, rndR, sqrL, sqrR;
    rndL = rndR = sqrL = sqrR = 0;
    
    string ans = s;
    for(int i = 0; i < s.length(); i++){
      
        if(s[i] == '(' || s[i] == ')'){
            if(rndL == rndR){
                ans[i] = '(';
                rndL++;
            }
            else
            {
                //向左回溯
                ans[i] = ')';
                int temp = i;
                while(temp >= 0){
                    i--;
                    
                }

            }

        }
        else if(s[i] == '[' || s[i] == ']'){
            if(sqrL == sqrR){
                ans[i] = '[';
                sqrL++;
            }
            else{
                ans[i] = ']';
                sqrR++;
            }

        }
    }

    return ans;
}

