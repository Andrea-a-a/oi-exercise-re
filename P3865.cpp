#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[100010][100];
int lg[100010];

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}


int main(){
    n = read();
    m = read();

    //ios::sync_with_stdio(0);

    lg[1] = 0;
    for(int i = 2; i <= n; i++){
        lg[i] = lg[i >> 1] + 1;
    }

    for(int i = 1; i <= n; i++){
        a[i][0] = read();
    }
    for(int j = 1; j <= lg[n]; j++){
        for(int o = 1; o <= n; o++){
            if(o + (1<<j) - 1 <= n){
                a[o][j] = max(a[o][j-1], a[o+(1<<(j-1))][j-1]); 
            }
        }
    }
    for(int i = 0; i < m; i++){
        int l, r;
        l = read();
        r = read();
        cout << max(a[l][lg[r-l+1]], a[r-(1<<lg[r-l+1])+1][lg[r-l+1]]);
        putchar('\n');

    }

    return 0;

}