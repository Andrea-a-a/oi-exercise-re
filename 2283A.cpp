//2283A
#include <bits/stdc++.h>
using namespace std;

void sol(){
	int l, r;
	cin >> l>> r;
	if(l == r){
			cout << "0\n";
		return;
	
	}
	if(l == 0 || r == 0){
		cout << max(abs(l),abs(r))-1 << "\n";
		return;
	}
	if(l > 0 || r < 0){
		cout << abs(abs(l)-abs(r)) << "\n";
		return;
	}
	if(abs(abs(l)-abs(r))>1)	cout << abs(abs(l)-abs(r))-1 << "\n";
	else{
		cout << "0\n";
	}
	
	return;
	
	
}

int main(){
	
	
	int n;
	cin >> n;
	while(n--){
		sol();
	}
}
