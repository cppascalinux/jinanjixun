#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=100100;
template <class nmsl> inline void read(nmsl &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}

int n, m, val[N], lastans;
int buc[N];
inline int min(int a, int b){return a<b? a:b;}
int main()
{
	freopen("busy.in", "r", stdin);
	freopen("busy.out", "w", stdout);
	read(n), read(m);
	for(R int i=1; i<=n; i++)read(val[i]), buc[val[i]]++;
	for(R int o=1, qa, qb, qc; o<=m; o++)
	{
		read(qa), read(qb), read(qc);
		qb^=lastans, qc^=lastans;
		if(qa==1)
		{
			if(qb==qc)continue;
			buc[qc]+=buc[qb], buc[qb]=0;
			for(R int i=1; i<=n; i++)if(val[i]==qb)val[i]=qc;
		}
		if(qa==2)
		{
			int ans=n+1, lastpos=0;
			if(!buc[qb] || !buc[qc])
			{
				printf("Chtholly\n");
				lastans=0;
				continue;
			}
			if(qb==qc)
			{
				printf("0\n");
				lastans=0;
				continue;
			}
			for(R int i=1, k=-1; i<=n; i++)
			{
				if(val[i]==qb && k==1)ans=min(ans, i-lastpos);
				if(val[i]==qb)
				{
					k=0;
					lastpos=i;
				}
				if(val[i]==qc && k==0)ans=min(ans, i-lastpos);
				if(val[i]==qc)
				{
					k=1;
					lastpos=i;
				}
			}
			printf("%d\n", ans);
			lastans=ans;
		}
	}
	return 0;
}
