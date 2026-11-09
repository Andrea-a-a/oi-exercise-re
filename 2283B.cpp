//2283B
#include <bits/stdc++.h>
using namespace std;

void sol(){
	int n;
	cin >> n;
	vector<long long> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	int ans = n-1;
	for(int i = 0; i < n; i++){
		int tmpans = 0;
		for(int o = 0; o < n; o++){
			if(a[o] % a[i] != 0){
				tmpans++;
			}
		}
		ans = min(ans, tmpans);
	}
	cout << ans << endl;
	
}

int main(){
	
	
	int n;
	cin >> n;
	while(n--){
		sol();
	}
}
