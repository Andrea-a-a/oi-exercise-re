#include <bits/stdc++.h>
using namespace std;
unordered_map<string, long long> a;
unordered_map<string, vector<string>> b;
int n;
const long long MOL = 1e9+7;

void shuchu(string name);
long long getval(string name);
long long process(string s);


int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        int opt;
        string name;
        cin >> opt >> name;
        if(opt == 3){
            //输出
            shuchu(name);
        }
        else{
            string p;
            //char u;
            //cin >> u;
            getline(cin, p);
            if(p[0] = ' ')  p = p.substr(1);
            ///cout << "     " << name  << "  " << p << endl;
            if(opt == 1){
                a[name] = process(p)%MOL;
                //直接赋值
            }
            else if(opt == 2){
                //间接赋值
                b[name] = p;
            }
        
        }
    }
    return 0;
}

void shuchu(string name){
    cout << getval(name)%MOL << endl;
}

//对字符串s进行解码，返回解码串的长度
long long process(string s){
    long long ans2 = 0;
    string ans = "";
    string now = "";
    int len = s.length();
    for(int i = 0; i < len && s[i] != '\0'; i++){
        if(s[i] == ' '){
            if(now[0] == '$'){
                ans2 += getval(now.substr(1));
                ans2 %= MOL;
            }
            else{
                ans2 += now.length();
                ans2 %= MOL;
            }
            now = "";

        }
        else{
            now += s[i];
        }
    }

    if(now[0] == '$'){
            ans2 += getval(now.substr(1));
            ans2 %= MOL;
    }
    else{
        ans2 += now.length();
        ans2 %= MOL;
    }
    
    return ans2%MOL;
}

//获得键为name的值的长度
long long getval(string name){
    
    if(a.find(name) != a.end()){
        return a[name]%MOL;
    }
    else if(b.find(name) != b.end()){
        return process(b[name])%MOL;
    }
    else{
        return 0;
    }
}