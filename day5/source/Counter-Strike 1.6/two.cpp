#include<bits/stdc++.h>
#define R register
#define ll long long
#define ull unsigned long long
#define log LOGGG
using namespace std;
const int N=1e5+10;
const ll base=10002019;
const ll mod=999983;
template <class nmsl> inline void read(nmsl &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
int n, hd[999985], bianshu, fk[N], Kk;
ull hashval[N], baseval[N];
ll ans;
char s[N];
struct abc{
	int nxt;
	ull val;
}qwq[10000010];
inline int insrt(ull v)
{
	int u=(v%mod);
	for(R int i=hd[u]; i; i=qwq[i].nxt)
		if(qwq[i].val==v)return 0;
	qwq[++bianshu].nxt=hd[u];
	qwq[bianshu].val=v;
	hd[u]=bianshu;
	return 1;
}
inline ull gethash(int l, int r)
{
	return hashval[r]-hashval[l-1]*baseval[r-l+1];
}
inline void pre()
{
	scanf("%s", s+1); n=strlen(s+1);
	read(Kk);
	baseval[0]=1;
	for(R int i=1; i<=n; i++)baseval[i]=baseval[i-1]*base, hashval[i]=hashval[i-1]*base+s[i];
	for(R int len=1; len<=n; len++)
	{
		for(R int i=1; i+len-1<=n; i++)
		{
			ull tp=gethash(i, i+len-1);
			if(insrt(tp))
			{
				for(R int j=i; j+len-1<=n; j++)
					if(gethash(j, j+len-1)==tp)fk[j]++, fk[j+len]--;
				int tmp=0;
				for(R int j=1, k=0; j<=n; j++)
				{
					if(k==0 && fk[j])tmp++;
					k+=fk[j];
					fk[j]=0;
				}
				if(tmp==Kk)ans++;
			}
		}
	}
	cout<<ans;
	return;
}
int main()
{
	freopen("two.in", "r", stdin);
	freopen("two.out", "w", stdout);
	pre();
	return 0;
}

