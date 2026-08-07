#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    vector<vector<string>> s(n);
    //读入
    cin.ignore();
    for(int i = 0; i < n; i++){
        string tmp;
        getline(cin, tmp);
        istringstream in(tmp);
        string t;
        while(in >> t){
            s[i].push_back(t);
        }
    }

    vector<int> abb(n, 0);

    while(true){
        map<string, vector<int>> m;
        for(int i = 0; i < n; i++){
            string w = "";
            int sz = s[i].size();

            //本轮缩写
            for(int o = 0; o < abb[i]; o++){
                w += s[i][o];
            }
            for(int o = abb[i]; o < sz; o++){
                w += s[i][o][0];
            }
            m[w].push_back(i);

        }

        vector<int> updateindex;
        for(auto u : m){
            if(u.second.size() > 1) {
                for(int i : u.second)   updateindex.push_back(i);
            }
        }

        if(updateindex.empty())   break;

        for(int i : updateindex){
            if(abb[i] < s[i].size())    abb[i]++;
        }


    }

    //输出
    
        for(int i = 0; i < n; i++){
            string w = "";
            int sz = s[i].size();

            //本轮缩写
            for(int o = 0; o < abb[i]; o++){
                w += s[i][o];
            }
            for(int o = abb[i]; o < sz; o++){
                w += s[i][o][0];
            }
            cout << w << endl;

        }

}