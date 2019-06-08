#include<iostream>
#include<cstdio>
using namespace std;
int n,f[100][100];
int main()
{
	freopen("loopy1.in","r",stdin);
	cin>>n; int cnt(0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>f[i][j];
			if(f[i][j]==-1)++cnt;
			else{
				cnt=0;
				if(cnt!=0)cout<<(char)(cnt+'a'-1);
				cout<<f[i][j];
			}
		}
	}
	return 0;
}
