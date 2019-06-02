#include<iostream>
#include<cstdio>
using namespace std;
int n,a[5002018];
int main()
{
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	if(n==1)cout<<"0"<<endl;
	else if(n==2){
		if(a[1]>a[2])cout<<"1"<<endl;
		else cout<<"0"<<endl;
	}
	else cout<<"Sorry, I don't know!"<<endl;
	fclose(stdin); fclose(stdout);
	return 0;
}
