#include <bits/stdc++.h>
using namespace std;

void delpan(string s);

int main(){

    //对于每一个左括号，入栈其index；对于发现右括号，出栈。
    //对于每一个substring，找到其中的所有括号括起来的部分，中间的删掉

    string r;
    cin >> r;
    
    
    stack<int> u;
    int len = r.length();
    for(int i = 0; i < len; i++){
        if(r[i] == '('){
            u.push(i);
            //cout << "pushed index " << i << endl;
        }
        else if(r[i] == ')'){
            int l = u.top();
            //cout << "poped index " << l << " to " << i << endl;
            u.pop();
            //cout << "substring : " << r.substr(l+1,i-l-1) << endl << "out: ";

            delpan(r.substr(l+1,i-l-1));
        }


    }

    
    //delpan(r);


    //对于每一个substring，使用正则表达式进行替换





    return 0;


}

//输入一个string，把里面的括号全干掉并输出，并且输入的string外面没有括号
void delpan (string s){
    int lft[200];
    int rt[200];

    lft[0] = 0;
    rt[0] = 0;

    int sz = s.size();

    if(s[0] != '(' && s[0] != ')')  cout << s[0];
    for(int i = 1; i < sz; i++){
        lft[i] = lft[i-1];
        rt[i] = rt[i-1];
        if(s[i-1] == '('){
            lft[i]++;
        }
        else if(s[i-1] == ')'){
            rt[i] ++;
        }
        if(lft[i] == rt[i] && s[i] != '(' && s[i] != ')'){
            cout << s[i];
        }
    }

    cout << endl;

}