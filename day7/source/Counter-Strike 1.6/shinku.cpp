#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=300010;
template <class swktqlaknoi> inline void read(swktqlaknoi &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
int n, m, buc[N], val[N];
int ans[N];
inline int max(int a, int b){return a>b? a:b;}
inline int min(int a, int b){return a<b? a:b;}
int main()
{
	freopen("shinku.in", "r", stdin);
	freopen("shinku.out", "w", stdout);
	read(n), read(m);
	for(R int i=1; i<=n; i++)read(val[i]);
	for(R int o=1, qa, qb; o<=m; o++)
	{
		int maxx=0, minn=11451419;
		for(R int i=1; i<=10; i++)ans[i]=0;
		read(qa), read(qb);
		for(R int i=qa; i<=qb; i++)buc[val[i]]=1, maxx=max(maxx, val[i]), minn=min(minn, val[i]);
		for(R int i=minn, k=0; i<=maxx+1; i++)
		{
			if(buc[i])k++;
			else 
			{
				if(k<=10 && k>=1)ans[k]++;
				k=0;
			}
		}
		for(R int i=qa; i<=qb; i++)buc[val[i]]=0;
		for(R int i=1; i<=10; i++)printf("%d", ans[i]%10);
		printf("\n");
	}
	return 0;
}
