#include <bits/stdc++.h>
using namespace std;

const int MAXS = 70;
const int MAXD = 130;

pair<string, string> s[MAXS];
vector<pair<string, string>> d;


string dict[16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
string huff;
int nd, ns, nn;

void quote(int index);
string getfirst(int index);
string decode(string s);

int chartoint(char x);

int main(){
    cin >> ns>> nd;
    for(int i = 1; i <= ns; i++){
        cin >> s[i].first >> s[i].second;
    }
    cin >> huff;
    int index = 0;
    cin >> nn;
    for(int o = 0; o < nn; o++){
        int opt, index;
        cin >> opt >> index;
        //引用
        if(opt == 1){
            quote(index);
        }
        
        else{
            string k, v;                
            if(index == 0){
                cin >> k >> v;
            }
            else{
                k = getfirst(index);
                cin >> v;
            }
            k = decode(k);
            v = decode(v);
            cout << k << ": " << v << endl;
            //字面量并索引指令
            if(opt == 2){
                d.insert(d.begin(), pair(k,v));
                if(d.size() > nd){
                    d.pop_back();
                }
                    
            }


        } 


    }

}






void quote(int index){
    if(index<=ns){
        cout << s[index].first << ": " << s[index].second << endl;
    }
    else{
        cout << d[index-ns-1].first << ": " << d[index-ns-1].second << endl;
    }
}
    


string getfirst(int index){
    if(index<=ns){
       return s[index].first;
    }
    else if(index <= ns + nd){
        return d[index-ns-1].first;
    }
    else{
        return "error when get first";
    }
    
}


string decode(string q){
    if(q[0] != 'H' || q.length() <= 1){
        return q;
    }
    else if(q[0] == 'H' && q[1] == 'H'){
        q = q.substr(1);
        return q;
    }
    cout << "error decoding";
    return " ";


}



int chartoint(char x){
    if(x >= '0' && x <= '9'){
        return x - '0';
    }
    else if(x >= 'a' && x <= 'f') { 
        return x - 'a' + 10;
    }
    else if (x >= 'A' && x <= 'F') {
        return x - 'A' + 10;
    }
    return 0;
}

