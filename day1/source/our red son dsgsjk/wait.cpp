#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int l[55],r[55],w[55],b[55],sum[55];
int main()
{
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	int n,m,i,j,cnt2,cnt=0,now,val;
	scanf("%d%d",&m,&n);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&l[i],&r[i],&w[i]);
		b[++cnt]=l[i],b[++cnt]=r[i]+1;
	}
	sort(b+1,b+cnt+1);
	cnt2=1;
	for(i=2;i<=cnt;i++)
		if(b[i]!=b[cnt2])
			b[++cnt2]=b[i];
	for(i=1;i<=m;i++)
	{
		l[i]=lower_bound(b+1,b+cnt2+1,l[i])-b;
		r[i]=lower_bound(b+1,b+cnt2+1,r[i]+1)-b;
//		printf("%d %d %d\n",i,l[i],r[i]);
	}
	for(i=0;i<(1<<m);i++)
	{
		memset(sum,0,sizeof(sum));
		for(j=1;j<=m;j++)
		{
			if(w[j]==-1)
			{
				if((1<<j-1)&i)
					val=1;
				else
					val=0;
			}
			else
				val=w[j];
			if(val==1)
				sum[l[j]]++,sum[r[j]]--;
			else
				sum[l[j]]--,sum[r[j]]++;
		}
		now=0;
		for(j=1;j<=cnt2;j++)
		{
			now+=sum[j];
			if(abs(now)>=2)
				break;
		}
		if(j>cnt2)
		{
			for(j=1;j<=m;j++)
			{
				if(w[j]==-1)
				{
					if((1<<j-1)&i)
						printf("1 ");
					else
						printf("0 ");
				}
				else
					printf("%d ",w[j]);
			}
			return 0;
		}
	}
	puts("-1");
	return 0;
}

