#include <iostream>
using namespace std;

long long n,m,a;

int main(){

    cin >> n >> m >> a;
    long long i = n/a, o = m/a;
    if( n%a!=0) i++;
    if( m%a!=0) o++;

    cout << i*o;

    return 0;
}