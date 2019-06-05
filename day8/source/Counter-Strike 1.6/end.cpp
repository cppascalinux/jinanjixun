#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=100100;
const ll mod=1000000007;
template <class nmsl> inline void read(nmsl &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
ll ans;
int n, k, lim, len, Kk;
char rubbish[N];
inline void dfs(int u, int done, int last)
{
	if(u==n)
	{
		if(done<lim && done>last)ans++;
		return;
	}
	for(R int i=last+1; i<lim; i++)
		dfs(u+1, done^i, i);	
	return;
}

int main()
{
	freopen("end.in", "r", stdin);
	freopen("end.out", "w", stdout);
	read(n), read(Kk);
	scanf("%s", rubbish+1);
	len=strlen(rubbish+1);
	for(R int j=1, k=0; j<=Kk; j++)
	for(R int i=len; i>=1; i--, k++)
		if(rubbish[i]=='1')lim+=(1<<k);
	dfs(1, 0, -1);
	cout<<ans%mod;
	return 0;
}
