#include<bits/stdc++.h>
#define swkakioi 1
#define ll long long
#define R register
using namespace std;
const int N=500010;
template <class swkaknoi> inline void read(swkaknoi &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
int n;
char s[N];
ll f[1010][1010];
int main()
{
	freopen("guess.in", "r", stdin);
	freopen("guess.out", "w", stdout);
	scanf("%s", s+1);
	n=strlen(s+1);
	for(R int k=1; k<=n+1; k++)
		for(R int i=1; i+k-1<=n+1; i++)
			f[i][k]=(1<<30);
	for(R int i=1; i<=n+1; i++)f[i][1]=0;
	for(R int i=1; i<=n; i++)f[i][2]=s[i]-'0';
	for(R int k=3; k<=n+1; k++)
		for(R int i=1; i+k-1<=n+1; i++)
			for(R int j=1; j<k; j++)
				f[i][k]=min(f[i][k], max(f[i][j], f[i+j][k-j])+(s[i+j-1]-'0'));
	cout<<f[1][n+1];
	return 0;
}
