#include <bits/stdc++.h>
using namespace std;

int n;
int NN, MM, nn, mm;
string original[70];
string firstline;

//原程序已经输出了index2行。
int index2;

void tacklingat(string s);
bool bar(void);

int main(){

    cin >> n;
    getline(cin, original[0]);
    for(int i = 1; i <= n; i++){
        getline(cin, original[i]);
        if(original[i][0] =='#'){
            i--;
        }
    }

        
    getline(cin, firstline);

    while(firstline[0] != '@'){
        getline(cin, firstline);
    }

    tacklingat(firstline);
    while(bar()){
        continue;
    }

    for(int i = index2+1; i <= n; i++){
        cout << original[i] << endl;
        
    }


    return 0;
}

//分析以@开头的字符串s，把值存到全局变量里
void tacklingat(string s){
    int len = s.length();
    s = s.substr(4,len-6);
    len = len-6;
    int index = 0;
    while(s[index] != ','){
        NN *= 10;
        NN += s[index] - '0';
        index++;
    }
    index++;
    while(s[index] != ' '){
        MM *= 10;
        MM += s[index] - '0';
        index++;
    }
    index++;
    index++;
    while(s[index] != ','){
        nn *= 10;
        nn += s[index] - '0';
        index++;
    }
    index++;
    while(s[index] != ' '){
        mm *= 10;
        mm += s[index] - '0';
        index++;
    }
}

bool bar(void){


    for(int i = index2+1; i < NN; i++){
        cout << original[i] << endl;
        
    }
    index2 = NN-1;

    //tacklingat(firstline);

    //string line;
    int minus = 0;
    int plus = 0;

    for(int i = 1; i < NN; i++){
        cout << original[i] << endl;
    }

index2 = NN+MM-1;

    while(getline(cin, firstline) && firstline[0] != '@'){
        if(firstline[0] == EOF || firstline.length() < 2) return false;
        if(firstline[0] == ' ')  cout << firstline.substr(1) << endl;
        else if(firstline[0] == '-'){
            minus ++;
        }
        else if(firstline[0] == '+'){
            plus++;
            cout << firstline.substr(1) << endl;
        }
    }


    tacklingat(firstline);
    return true;


}
