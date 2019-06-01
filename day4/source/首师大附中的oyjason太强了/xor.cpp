#include<map>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=202020;
map<int,int>mp;
int a[N*4][31],ans[N],ca[N],w[N];
vector<int>s[N*4];
void ins(int root,int w)
{
	int i;
	for(i=30;i>=1;i--)
	{
		if((1<<i-1)&w)
		{
			if(!a[root][i])
				a[root][i]=w;
			w^=a[root][i];
			if(!w)
				return;
		}
	}
}
inline void solve(int root,int left,int right)
{
	int i,mid=left+right>>1,y,sum;
	for(i=1;i<=30;i++)
		a[root][i]=a[root/2][i];
	for(i=0;i<s[root].size();i++)
	{
		y=s[root][i];
		ins(root,y);
	}
	if(left==right)
	{
		sum=0;
		for(i=1;i<=30;i++)
			if(a[root][i])
				sum++;
		ans[left]=(1<<sum);
		return;
	}
	solve(root*2,left,mid);
	solve(root*2+1,mid+1,right);
}
inline void update(int root,int left,int right,int x,int y,int w)
{
	if(x<=left&&y>=right)
	{
		s[root].push_back(w);
		return;
	}
	int mid=left+right>>1;
	if(mid>=x)
		update(root*2,left,mid,x,y,w);
	if(mid<y)
		update(root*2+1,mid+1,right,x,y,w);
}
inline int read()
{
	char ch='a';int ans=0;
	for(;ch>'9'||ch<'0';ch=getchar());
	for(;ch<='9'&&ch>='0';ch=getchar()) ans=ans*10+ch-'0';
	return ans;
}
int main()
{
	int m,q,i,cnt=0;
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	m=read(),q=read();
	for(i=1;i<=q;i++)
	{
		ca[i]=read(),w[i]=read();
		if(ca[i]==1)
			mp[w[i]]=i;
		else
		{
			update(1,1,q,mp[w[i]],i-1,w[i]);
			mp[w[i]]=0;
		}
	}
	for(i=1;i<=q;i++)
	{
		if(mp[w[i]])
			update(1,1,q,mp[w[i]],q,w[i]);
	}
	solve(1,1,q);
	for(i=1;i<=q;i++)
		printf("%d\n",ans[i]);
	return 0;
}

