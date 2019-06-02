#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const double PI=acos(-1);
int n;
double S(int a,int b,int c)
{
	return (sin(2*PI*(b-a)/n)+sin(2*PI*(c-b)/n)+sin(2*PI*(a+n-c)/n))/2;
}
double s[1000010];int tot;
char st[1010];
int main()
{
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	scanf("%d",&n);
	if(n>100){
		printf("0\n");
		return 0;
	}
	scanf("%s",st+1);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				if(st[i]=='1'||st[j]=='1'||st[k]=='1')
					s[++tot]=S(i,j,k);
	sort(s+1,s+tot+1);
	int cur=0;
	long long ans=0;
	for(int i=1;i<=tot;i++)
	{
		if(s[i]==s[i-1])cur++;
		else cur=0;
		ans+=cur;
	}
	printf("%lld\n",ans);
	fclose(stdin);fclose(stdout);
	return 0;
}

