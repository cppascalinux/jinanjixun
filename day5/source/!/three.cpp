#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,ans;
bool a[100005];
char s[100005];
int calc(int i,int j,int k)
{
	int x=j-i,y=k-j,z=k-i;
	x=min(x,n-x),y=min(y,n-y),z=min(z,n-z);
	if(x>y)swap(x,y);
	if(x>z)swap(x,z);
	if(y>z)swap(y,z);
	return x*10000+y*100+z;
}
int main()
{
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)a[i]=(s[i]=='1');
	if(n>10)
	{
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	for(int k=j+1;k<=n;k++)
	{
		if(a[i]==0&&a[j]==0&&a[k]==0)continue;
		for(int i2=i;i2<=n;i2++)
		for(int j2=i==i2?j:i2+1;j2<=n;j2++)
		for(int k2=i==i2&&j==j2?k:j2+1;k2<=n;k2++)
		{
			if(a[i2]==0&&a[j2]==0&&a[k2]==0)continue;
			if(i==i2&&j==j2&&k==k2)continue;
			if(calc(i,j,k)==calc(i2,j2,k2))ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
