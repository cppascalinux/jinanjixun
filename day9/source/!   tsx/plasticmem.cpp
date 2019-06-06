#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,a[1000005];
void printi(unsigned x)
{
	printf("%d",x%2);
	if(x>=2)printi(x/2);
}
inline int getcnt(unsigned x)
{
	x=((x&0x55555555)+((x>>1)&0x55555555));
	x=((x&0x33333333)+((x>>2)&0x33333333));
	x=((x&0x0f0f0f0f)+((x>>4)&0x0f0f0f0f));
	x=((x&0x00ff00ff)+((x>>8)&0x00ff00ff));
	x=((x&0x0000ffff)+((x>>16)&0x0000ffff));
	return x;
}
struct mybit
{
	unsigned val[3405];
	mybit(){memset(val,0,sizeof(val));}
	inline bool getval(int x) const
	{
		return !!(val[x/32]&(1u<<(x%32)));
	}
	inline void getst(int x,int v)
	{
		if(v==0) val[x/32]&=(~(1u<<(x%32)));
		else val[x/32]|=(1u<<(x%32));
	}
	inline mybit operator &(const mybit &x) const
	{
		mybit y;
		for(int i=0;i<=n/32;i++)
			y.val[i]=val[i]&x.val[i];
		return y;
	}
	inline mybit operator |(const mybit &x) const
	{
		mybit y;
		for(int i=0;i<=n/32;i++)
			y.val[i]=val[i]|x.val[i];
		return y;
	}
	inline mybit operator <<(const int x) const
	{
		mybit y;
		for(int i=0;i<=n/32;i++)
			y.val[i]=(val[i]<<x);
		for(int i=1;i<=n/32;i++)
			y.val[i]|=(val[i-1]>>(32-x));
		return y;
	}
	inline mybit operator >>(const int& x) const
	{
		mybit y;
		for(int i=0;i<=n/32;i++)
			y.val[i]=(val[i]>>x);
		for(int i=0;i<n/32;i++)
			y.val[i]|=(val[i+1]<<(32-x));
		return y;
	}
	inline void getcr(const int& l,const int& r,const int& v)
	{
		if(l/32==r/32)
		{
			for(int i=l;i<=r;i++)
				(*this).getst(i,v);
			return;
		}
		for(int i=l;i/32==l/32;i++)
			(*this).getst(i,v);
		for(int i=r;i/32==r/32;i--)
			(*this).getst(i,v);
		for(int i=l/32+1;i<r/32;i++)
			if(v==0) val[i]=0;
			else val[i]=((unsigned)-1);
	}
	inline int getct(const int& l,const int& r)
	{
		int ans=0;
		if(l/32==r/32)
		{
			for(int i=l;i<=r;i++)
				ans+=(*this).getval(i);
			return ans;
		}
		for(int i=l;i/32==l/32;i++)
			ans+=(*this).getval(i);
		for(int i=r;i/32==r/32;i--)
			ans+=(*this).getval(i);
		for(int i=l/32+1;i<r/32;i++)
			ans+=getcnt(val[i]);
		return ans;
	}
	inline void getand(const mybit &x,const int &l,const int &r)
	{
		int ans=0;
		if(l/32==r/32)
		{
			for(int i=l;i<=r;i++)
				(*this).getst(i,(*this).getval(i)&(x.getval(i)));
			return;
		}
		for(int i=l;i/32==l/32;i++)
			(*this).getst(i,(*this).getval(i)&x.getval(i));
		for(int i=r;i/32==r/32;i--)
			(*this).getst(i,(*this).getval(i)&x.getval(i));
		for(int i=l/32+1;i<r/32;i++)
			val[i]=(val[i]&x.val[i]);
	}
	/*void print()
	{
		for(int i=0;i<=n/32;i++)
			printi(val[i]),printf(" ");
		printf("\n");
	}*/
}b;
int main()
{
	freopen("plasticmem.in","r",stdin);
	freopen("plasticmem.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(n<=1000&&m<=1000)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=m;i++)
		{
			int op,l,r;
			scanf("%d%d%d",&op,&l,&r);
			if(op==1)
			{
				for(int i=l;i<=r;i++)
					a[i]=0;
			}
			if(op==2)
			{
				for(int i=l;i<=r;i++)
					a[i]=1;
			}
			if(op==3)
			{
				for(int i=l;i<r;i++)
					a[i]|=a[i+1];
			}
			if(op==4)
			{
				for(int i=r;i>l;i--)
					a[i]|=a[i-1];
			}
			if(op==5)
			{
				for(int i=l;i<r;i++)
					a[i]&=a[i+1];
			}
			if(op==6)
			{
				for(int i=r;i>l;i--)
					a[i]&=a[i-1];
			}
			if(op==7)
			{
				int ans=0;
				for(int i=l;i<=r;i++)
					ans+=a[i];
				printf("%d\n",ans);
			}
		}
		return 0;
	}
	if(n<=100000&&m<=100000)
	{
		for(int i=0;i<n;i++)
		{
			int x;
			scanf("%d",&x);
			b.getst(i,x);
		}
		for(int i=1;i<=m;i++)
		{
			int op,l,r;
			scanf("%d%d%d",&op,&l,&r);
			l--,r--;
			if(op==1) b.getcr(l,r,0);
			if(op==2) b.getcr(l,r,1);
			if(op==3)
			{
				if(l==r) continue;
				mybit c;
				c.getcr(l+1,r,1);
				//printf("c=");
				//c.print();
				c=(c&b);
				//printf("nc=");
				//c.print();
				c=(c>>1);
				//printf("nnc=");
				//c.print();
				b=(c|b);
			}
			if(op==4)
			{
				if(l==r) continue;
				mybit c;
				c.getcr(l,r-1,1);
				c=(c&b);
				c=(c<<1);
				b=(c|b);
			}
			if(op==5)
			{
				if(l==r) continue;
				mybit c;
				c.getcr(l+1,r,1);
				c=(c&b);
				c=(c>>1);
				b.getand(c,l,r-1);
			}
			if(op==6)
			{
				if(l==r) continue;
				mybit c;
				c.getcr(l,r-1,1);
				c=(c&b);
				c=(c<<1);
				b.getand(c,l+1,r);
			}
			if(op==7) printf("%d\n",b.getct(l,r));
			//b.print();
		}
	}
	return 0;
}
