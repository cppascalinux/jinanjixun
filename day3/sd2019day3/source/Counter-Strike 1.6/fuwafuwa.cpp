#include<bits/stdc++.h>
#define R register
#define ll long long
#define int long long
using namespace std;

template <class nmsl> inline void read(nmsl &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
ll pol, root, ls[5000000], rs[5000000], T, n;
ll  a, b, m;
ll val[5000000];
inline int BST_insrt(int &pos, ll x)
{
//	cout<<pos<<" awsl "<<x<<endl;
	if(!pos){pos=++pol; val[pos]=x; return 0;}
	if(x<val[pos])return BST_insrt(ls[pos], x)+1;
	else return BST_insrt(rs[pos], x)+1;
	return 0;
}
signed main()
{
	freopen("fuwafuwa.in", "r", stdin);
	freopen("fuwafuwa.out", "w", stdout);
	read(T);
	while(T--)
	{
//		for(R int i=1; i<=pol; i++)val[i]=ls[i]=rs[i]=0;
		root=0;
		read(a), read(b), read(m), read(n);
		for(R ll i=1; i<=n; i++)
		{
//			cout<<i<<" "<<(a+i*b)%m<<endl;
			if(i<n)BST_insrt(root, (a+i*b)%m);
			else printf("%lld\n", BST_insrt(root, (a+i*b)%m));
		}
	}
	return 0;
}
