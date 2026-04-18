#include <iostream>
using namespace std;

int N, M;
string s;
void act1();
void act2();
void act3();
void stoi();

string itostr(){
    string w = "";
    int n;
    cin >>  n;
    for(int i = 0; i < n; i++){
        int tmp;
        cin >> tmp;
        w+='a'+tmp-1;
    }

    return w;
}


int main (){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        int tmp;
        cin >> tmp;
        s += 'a'+tmp-1;
    }
    for(int i = 0; i < M; i++){
        int opt;
        cin >> opt;
        if(opt == 1){
            act1();
        }
        else if(opt == 2){
            act2();
        }
        else if(opt == 3){
            act3();
        }
    }
    stoi();
    return 0;
}

void act1(){
    string befind = itostr();
    string repla = itostr();
    
    if(s.find(befind) != s.npos){
        s.replace(s.find(befind), befind.size(), repla);
    }
}

void act2(){
    int sz = s.size();

    for(int i = 0; i < sz-1; i++){
        if((s[i]-'a' + s[i+1]-'a')%2 == 0){
            s.insert(i+1,1, (s[i]+s[i+1])/2);
            i = i+1;
            sz+=1;
        }

    }

    //cout << "action 2 finished." << endl;


}

void act3(){
    int l, r;
    cin >> l >> r;
    string p = "";
    int sz = r-l+1;
    for(int i = 0; i < sz; i++){
        p+=s[r-i-1];
    }

    //cout << "string p: " << p << endl;
    s.replace(l-1, sz, p);


}

void stoi(){
    int sz = s.size();
    for(int i = 0; i < sz-1; i++){
        cout << s[i] - 'a' +1 << " ";
    }
    cout << s[sz-1] - 'a' +1<<endl;


}