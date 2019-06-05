#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
int main()
{
	freopen("shinku.in","w",stdout);
	int n=20000,m=20000;
	cout<<n<<" "<<m<<endl;
	for(int i=1;i<=n;i++)cout<<rand()%20000+1<<" ";
	for(int i=1;i<=m;i++){
		cout<<"1 20000"<<endl;
	}
	return 0;
}
