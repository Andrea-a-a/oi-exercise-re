#include <iostream>
using namespace std;


int main(){


    for(int i = 100; i < 1000; i++){
        int sum = i/100 + i% 10 + (i % 100)/10;
        int sumsum = sum / 100 + sum % 10 + (sum % 100)/10;
        if(sum == sumsum ){
            cout << i << endl;
        }


    }
    cout << "miao";

    return 0;


}