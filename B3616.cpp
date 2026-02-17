#include <bits/stdc++.h>
using namespace std;

queue<long long> q;

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int opt;
        cin >> opt;
        if(opt == 1){
            long long o;
            cin >> o;
            q.push(o);
        }
        else if(opt == 2){
            if(!q.empty())    q.pop();
            else    cout << "ERR_CANNOT_POP" << endl;
        }
        else if(opt == 3){
            if(q.empty())   cout << "ERR_CANNOT_QUERY" << endl;
            else    cout << q.front() << endl; 
        }
        else if(opt == 4){
            cout << q.size() << endl;
        }
    }


    return 0;
}