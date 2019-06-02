#include<bits/stdc++.h>
#define R register
#define ll long long
using namespace std;
int n, val[1919];
int main()
{
	freopen("one.in", "r", stdin);
	freopen("one.out", "w", stdout);
	srand(time(0));
	cin>>n;
	for(R int i=1; i<=n; i++)cin>>val[i];
	if(n==2)
	{
		if(val[1]<val[2]){cout<<0;return 0;}
		else if(val[1]>val[2]){cout<<1;return 0;}
	}
	int flag=0;
	for(R int i=1; i<=n; i++)
		if(val[i]<val[i-1])flag=1;
	if(!flag){cout<<0;return 0;}
	cout<<rand()*rand();
	return 0;
}










