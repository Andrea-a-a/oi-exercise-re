#include <iostream>
#include <vector>
using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;
        vector<long long> three, two, other, six;

        while(n--){
            long long tmp;
            cin >> tmp;
            if(tmp % 2 == 0){
                if(tmp % 3 == 0)    six.push_back(tmp);
                else    two.push_back(tmp);
            }
            else if(tmp % 3 == 0){
                three.push_back(tmp);
            }
            else{
                other.push_back(tmp);
            }
        }
        for(auto x : three) cout << x << " ";
        for(auto x : other) cout << x << " ";
        for(auto x : two)   cout << x << " ";
        for(auto x : six)   cout << x << " ";
        cout << endl;
    }




    return 0;
}