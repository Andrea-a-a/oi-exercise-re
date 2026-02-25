#include <iostream>

using namespace std;

int t;

bool isValid(int, string);


int main(){
    cin >> t;

    for(int p = 0; p < t; p++){
        int n;
        string s;
        cin >> n >> s;
        if(n % 2 != 0){
            if(s[0] == 'b'){
                cout << "NO" << endl;
                continue;
            }

            n--;
            s = s.substr(1);


        }
        if(isValid(n, s)){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }



    }


    return 0;




}

bool isValid(int n, string s){

    for(int i = 0; i < n; i += 2){
        if(s[i] == '?' || s[i+1] == '?'){
            continue;
        }
        else if(s[i] == 'a' && s[i+1] == 'a'){
            return false;
        }
        else if(s[i] == 'b' && s[i+1] == 'b'){
            return false;
        }
    }

    return true;




}