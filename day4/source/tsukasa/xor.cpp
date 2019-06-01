#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;
#define MAXN 111111
#define pii pair<int,int> 
#define mp make_pair 
#define lson node<<1
#define rson node<<1|1

int read()
{
	int ret=0,neg=1;
	char c=getchar();
	while (c<'0' || c>'9'){
		if (c=='-') neg=-1;
		c=getchar();
	}
	while (c>='0' && c<='9'){
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*neg;
}

int m,q;
vector<int> tree[MAXN<<2];
int ji[MAXN<<2][33];
int cnt[MAXN<<2];
set<pii> s;

void insert(int node,int l,int r,int x,int y,int val)
{
	if (l==x && r==y){
		tree[node].push_back(val);
		return;
	}
	int mid=((r-l)>>1)+l;
	if (y<=mid) insert(lson,l,mid,x,y,val);
	else if (x>mid) insert(rson,mid+1,r,x,y,val);
	else{
		insert(lson,l,mid,x,mid,val);
		insert(rson,mid+1,r,mid+1,y,val);
	}
}

void add(int node,int x)
{
	for (int i=m;i>=0;i--) if(x&(1ll<<i)){
		if (!ji[node][i]){
			ji[node][i]=x;
			cnt[node]++;
			break;
		}
		x^=ji[node][i];
	}
}

void calc(int node,int l,int r)
{
	for (int i=0;i<=m;i++) ji[node][i]=ji[node>>1][i];cnt[node]=cnt[node>>1];
	int len=tree[node].size();
	for (int i=0;i<len;i++) add(node,tree[node][i]);
	if (l==r){
		printf("%d\n",1<<cnt[node]);
		return;
	}
	int mid=((r-l)>>1)+l;
	calc(lson,l,mid);calc(rson,mid+1,r);
}

int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	m=read();q=read();
	for (int i=1;i<=q;i++){
		int ope=read(),x=read();
		if (ope==1)
			s.insert(mp(x,i));
		else{
			pii now=*(s.lower_bound(mp(x,0)));
			insert(1,1,q,now.second,i-1,x);
			s.erase(now);
		}
	}
	set<pii>::iterator i;
	for(i=s.begin();i!=s.end();i++)insert(1,1,q,(*i).second,q,(*i).first);
	calc(1,1,q);
}
