#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=1e5+10;
template <class nmsl> inline void read(nmsl &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
int T, n, m, anum, bnum, num;
int lt[N], rt[N];
int main()
{
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	read(T);
	while(T--)
	{
		read(n), read(m); num=0; anum=bnum=0;
		for(R int i=1, qa; i<=n; i++)
		{
			read(qa);
			if(qa&1)
			{
				lt[++num]=i;
				while(qa&1 && i<n)read(qa), i++;
				rt[num]=i-1;
				anum+=rt[num]-lt[num]+1;
			}
		}
		bnum=n-anum;
		if(n==1)
		{
			if(anum)printf("A\n");
			else printf("B\n");
			continue;
		}
		if((n&1) && m){printf("A\n");continue;}
		if(!(n&1) && !m){printf("A\n");continue;}
		if(bnum==n){printf("A\n");continue;}
		if(m==1)bnum--;
		for(R int i=1; i<=num; i++)
		{
			int len=rt[i]-lt[i]+1;
			if(len&1)bnum-=1;
		}
		bnum++;
		if(bnum)printf("A\n");
		else printf("B\n");
	}
	return 0;
}
