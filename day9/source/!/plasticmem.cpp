#include<cstdio>
#include<algorithm>
#include<cstring>
#include<bitset>
using namespace std;
int n,m,b[1000005];
int st[1000005],col[1000005],top;
int tmp[1000005],c[1000005],top2;
bitset<100005>a,tmp1;
int main()
{
	freopen("plasticmem.in","r",stdin);
	freopen("plasticmem.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(n<=100000&&m<=100000)
	{
		for(int i=1;i<=n;i++)
		{
			int p;
			scanf("%d",&p);
			a[i]=p;
			tmp1[i]=1;
		}
		while(m--)
		{
			int opt,l,r;
			scanf("%d%d%d",&opt,&l,&r);
			if(opt==1)a&=(tmp1<<r)|(tmp1>>(n-l+1));
			if(opt==2)a|=(tmp1<<(l-1))&(tmp1>>(n-r));
			if(opt==3)a|=(a&(tmp1<<l)&(tmp1>>(n-r)))>>1;
			if(opt==4)a|=(a&(tmp1<<(l-1))&(tmp1>>(n-r+1)))<<1;
			if(opt==5)a&=(a|(tmp1<<r)|(tmp1>>(n-l)))>>1;
			if(opt==6)a&=(a|(tmp1<<(r-1))|(tmp1>>(n-l+1)))<<1;
			if(opt==7)printf("%llu\n",(a&(tmp1<<(l-1))&(tmp1>>(n-r))).count());
		}
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		if(i==1||b[i]!=b[i-1])
		{
			st[++top]=i;
			col[top]=b[i];
		}
	}
	while(m--)
	{
		int opt,L,R;
		scanf("%d%d%d",&opt,&L,&R);
		top2=0;
		if(opt==1)
		{
			while(top>=1&&st[top]>R+1)
			{
				tmp[++top2]=st[top];
				c[top2]=col[top--];
			}
			tmp[++top2]=R+1;
			c[top2]=col[top];
			while(top>=1&&st[top]>=L)top--;
			st[++top]=L;
			col[top]=0;
			while(top>=2&&col[top]==col[top-1])top--;
			while(top2)
			{
				st[++top]=tmp[top2];
				col[top]=c[top2--];
				while(top>=2&&col[top]==col[top-1])top--;
			}
		}
		if(opt==2)
		{
			while(top>=1&&st[top]>R+1)
			{
				tmp[++top2]=st[top];
				c[top2]=col[top--];
			}
			tmp[++top2]=R+1;
			c[top2]=col[top];
			while(top>=1&&st[top]>=L)top--;
			st[++top]=L;
			col[top]=1;
			while(top>=2&&col[top]==col[top-1])top--;
			while(top2)
			{
				st[++top]=tmp[top2];
				col[top]=c[top2--];
				while(top>=2&&col[top]==col[top-1])top--;
			}
		}
		if(opt==3)
		{
			for(int i=1;i<=top;i++)
			{
				if(st[i]<=L)continue;
				if(st[i]>R)break;
				if(col[i]==0)continue;
				st[i]--;
				if(st[i]==st[i-1])col[i-1]=col[i];
			}
			for(int i=1;i<=top;i++)
			{
				tmp[++top2]=st[i];
				c[top2]=col[i];
				while(top2>=2&&c[top2]==c[top2-1])top2--;
			}
			top=top2;
			for(int i=1;i<=top;i++)
			  st[i]=tmp[i],col[i]=c[i];
		}
		if(opt==4)
		{
			for(int i=1;i<=top;i++)
			{
				if(st[i]<=L)continue;
				if(st[i]>R)break;
				if(col[i]==1)continue;
				st[i]++;
				if(st[i]==st[i+1])col[i]=col[i+1];
			}
			for(int i=1;i<=top;i++)
			{
				tmp[++top2]=st[i];
				c[top2]=col[i];
				while(top2>=2&&c[top2]==c[top2-1])top2--;
			}
			top=top2;
			for(int i=1;i<=top;i++)
			  st[i]=tmp[i],col[i]=c[i];
		}
		if(opt==5)
		{
			for(int i=1;i<=top;i++)
			{
				if(st[i]<=L)continue;
				if(st[i]>R)break;
				if(col[i]==1)continue;
				st[i]--;
				if(st[i]==st[i-1])col[i-1]=col[i];
			}
			for(int i=1;i<=top;i++)
			{
				tmp[++top2]=st[i];
				c[top2]=col[i];
				while(top2>=2&&c[top2]==c[top2-1])top2--;
			}
			top=top2;
			for(int i=1;i<=top;i++)
			  st[i]=tmp[i],col[i]=c[i];
		}
		if(opt==6)
		{
			for(int i=1;i<=top;i++)
			{
				if(st[i]<=L)continue;
				if(st[i]>R)break;
				if(col[i]==0)continue;
				st[i]++;
				if(st[i]==st[i+1])col[i]=col[i+1];
			}
			for(int i=1;i<=top;i++)
			{
				tmp[++top2]=st[i];
				c[top2]=col[i];
				while(top2>=2&&c[top2]==c[top2-1])top2--;
			}
			top=top2;
			for(int i=1;i<=top;i++)
			  st[i]=tmp[i],col[i]=c[i];
		}
		if(opt==7)
		{
			int ans=0;
			for(int i=1;i<top;i++)
			{
				if(st[i+1]<=L)continue;
				if(st[i]>R)continue;
				if(col[i]==0)continue;
				ans+=min(st[i+1],R+1)-max(st[i],L);
			}
			if(st[top]<=R&&col[top]==1)ans+=R+1-max(st[top],L);
			printf("%d\n",ans);
		}
//		for(int i=1;i<=top;i++)
//		  printf("%d %d\n",st[i],col[i]);
	}
	return 0;
}
