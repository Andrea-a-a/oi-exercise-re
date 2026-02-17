#include <iostream>
using namespace std;
int t;
const int MAXN = 2e5+10;


int main(){
    cin >> t;
    for(int i = 0; i < t; i++){
        int n;
        int a[MAXN];
        int front = 0;
        int maxindex = 0;
        cin >> n;
        for(int o = 1; o <= n; o++){
            cin >> a[o];
            //if(a[o] == n)   maxindex = o;
        }
        for(int o = 1; o <= n; o++){
            if(a[o] != n+1-o){
                break;
            }
            else{
                front = o;
            }
        }
        for(int o = front + 1; o <= n; o++){
            if(a[o] == n - front)   maxindex = o;
        }



        //cout << "       front : " << front << "    maxindex : " << maxindex << endl;
        if(front == n){
            for(int o = 1; o <= n; o++){
                cout << a[o] << " ";
            }
            cout << endl;
        }
        else{
            for(int o = 1; o <= front; o++){
                cout << a[o] << " ";
            }
            for(int o = maxindex; o > front; o--){
                cout << a[o] << " ";
            }
            for(int o = maxindex + 1; o <= n; o++){
                cout << a[o] << " ";
            }
            cout << endl;
        }


    }




}