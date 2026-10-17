#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    int id = argc > 1 ? atoi(argv[1]) : 0;
    //cout << id;
    if(id == 0){
        int n;
        cin >> n;
        vector<long long> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        cout << n << '\n';
        for(int i = 0; i< n; i++){
            cout << a[i] << " " ;
        }
        cout << endl;

        int o;
        cin >> o;
        cout << o << endl;
    }

    else if(id == 1){
        int n1, n2;
        cin >> n1;
        vector<long long> a(n1);
        for(int i = 0; i < n1; i++){
            cin >> a[i];
        }
        cin >> n2;
        vector<long long> b(n2);
        for(int i = 0; i < n2; i++){
            cin >> b[i];
        }
        if(n1 != n2){
            cout << "0" << endl;
            return 0;
        }
        sort(a.begin(), a.end());
        for(int i = 0; i < n1; i++){
            if(a[i] != b[i]) { cout << "0" << endl;
            return 0;}
            
        }
        cout << "1" << endl;
        return 0;
    }


}