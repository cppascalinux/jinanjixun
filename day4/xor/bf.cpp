#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
using namespace std;
int m,q;
int f[1050009],sz[1050009];
int fnd(int x)
{
	return x==f[x]?x:f[x]=fnd(f[x]);
}
int main()
{
	freopen("xor.in","r",stdin);
	freopen("bf.out","w",stdout);
	scanf("%d%d",&m,&q);
	for(int i=0;i<1<<m;i++)
		f[i]=i,sz[i]=1;
	for(int i=1,a,b;i<=q;i++)
	{
		scanf("%d%d",&a,&b);
		for(int j=0;j<1<<m;j++)
			if(fnd(j)!=fnd(b^j))
			{
				f[fnd(j)]=fnd(b^j);
				sz[fnd(b^j)]+=sz[fnd(j)];
			}
		int lst=-1;
		for(int j=0;j<1<<m;j++)
			if(fnd(j)==j)
			{
				if(lst==-1)
					lst=sz[fnd(j)];
				else if(lst!=sz[fnd(j)])
					cerr<<"WA"<<endl,assert(1);
			}
	}
	return 0;
}