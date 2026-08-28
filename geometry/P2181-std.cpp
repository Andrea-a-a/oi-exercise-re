#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long n;
    unsigned long long ans;
    ans=0;
	cin>>n;
	for(int i=1;i<=n-3;i++)
	    ans+=(n-i-2)*i;
	if(ans%4==0)
	    ans=ans/4*n;
	else if(ans%2==0)
	        ans=ans/2*n/2;
	    else if(ans%2==1)
	            ans=n/4*ans;
	cout<<ans;
	return 0;
}
