#include <bits/stdc++.h>
using namespace std;

#define getchar_unlocked getchar;

long long in(){
    long long k = 0;
    int f = 1;
    char c = getchar();
    while(c < '0'){
        if(c == '-')    f = -1;
        c = getchar();
    }
    
    

    while('0' <= c){
        k = (k << 1) + (k << 3) + (c ^ 48);
        c = getchar();
    }
    return k*f;

}

void out(long long k){
    if(k < 0){
        putchar('-');
        k = -k;
    }
    if(k < 10){
        putchar(k + '0');
    }
    else{
        out(k/10);
        putchar(k%10 + '0');
    }
}


int main(){

    long long sum = 0;
    long long m = in();
    for(long long i = 0; i < m; i++){
        sum += in();
    }
    out(sum);

    return 0;
}