#include <iostream>
using namespace std;

int main(){



    return 0;
}#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std ;
const int MAXN = 5e5 + 7 ;
int a[MAXN] ;
int n , m ;

int tr[MAXN] ;
void add(int u , int num) {//i表示初始更改的结点，num表示加上的值
	while (u <= n) {
		tr[u] += num ;
		u += lowbit(u) ;
	}
}
int query(int u) {
	int ans = 0 ;
	while (u > 0) {
		ans += tr[u] ;
		u -= lowbit(u) ;
	}
	return ans ;
}

signed main() {
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	
	cin >> n >> m ;
	for (int i = 1 ; i <= n ; i ++) {
		cin >> a[i] ;
		add(i , a[i]) ;
	}
	
	for (int i = 1 , opt , x , y ; i <= m ; i ++) {
		cin >> opt >> x >> y ;
		if (opt == 1) {
			add(x , y) ;
		}
		else {
			cout << query(y) - query(x - 1) << "\n" ;
		}
	}
	
	return 0 ;
}
