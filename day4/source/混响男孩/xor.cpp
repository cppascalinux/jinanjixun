#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<iostream>
#include<cstring>
#include<map>
#include <stack>
#define ll long long
#define maxn 140005
#define re(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){char c=getchar();int f=1;int ans = 0;while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();}while(c<='9'&&c>='0'){ans =ans*10+c-'0';c=getchar();}return ans*f;}
//_____________________________________________________________________________________________________
int n,m,root,tot_a;
struct node
{
	int l,r,len,v[35],head;
}a[maxn*2];
int tot_l;
struct list
{
	int v,nxt;
}li[maxn*20*4];
map <int,int> time;
stack<int> st;
#define p(x) printf("%d ",x)
#define P printf("\n")
void build(int&x,int l,int r)
{
//	p(l);p(r);P;
	x = ++tot_a;
	if(l==r) return;
	int mid = l+r>>1;
	build( a[x].l , l,mid );
	build( a[x].r ,mid+1,r );
}
int ans[maxn];
void insert(int x,int l,int r,int L,int R,int v)
{
	if(l>R||L>r) return;
	if(l>=L&&r<=R)
	{
		li[++tot_l] = (list){ v,a[x].head };
		a[x].head = tot_l;
		return;
	}
	int mid = l+r>>1;
	insert( a[x].l ,l,mid,L,R,v );
	insert( a[x].r ,mid+1,r,L,R,v );
}
void dfs(int x,int fa,int l,int r)
{
//	p(l);p(r);P;
	a[x].len = a[fa].len ;
	re( i,0,31 ) a[x].v [i] = a[fa].v [i] ;
	for(int i=a[x].head ;i;i= li[i].nxt )
	{
		int v = li[i].v;
	//	p(v);P;
		for(int j=31;~j;j--)
			if((v>>j)&1)
			{
				if(!a[x].v[j])
				{
					a[x].v [j] = v;
					++a[x].len ;
					break;
				}
				else v^=a[x].v [j];
			}
	}
	int mid = l+r>>1;
	if(l==r)
	{
		ans[l] = a[x].len ;
		return;
	}
	dfs( a[x].l,x,l,mid );
	dfs( a[x].r,x,mid+1,r ); 
	
}
int tot_q;/*
struct query
{
	int l,r,v;
}Q[maxn];*/
int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
    read();int q=read();
    build(root,1,q);
    re(i,1,q)
    {
    	int opt = read() , v = read();
    	if(opt==1) 
		{
			time[v] = i; 
			st.push(v);
		}
    	else 
		{
			//Q[++tot_q] = (query){time[v],now,v};
			insert( root,1,q,time[v],i-1,v );
		//	printf("%d %d %d\n",time[v],i,v);
			time[v] = 0;
		}
	}
	while(!st.empty())
	{
		int v = st.top();st.pop();
		if(time[v])
		{
		//	Q[++tot_q] = (query){time[v],now,v};
			insert( root,1,q,time[v],q,v );
		//	printf("%d %d %d\n",time[v],q,v);
			time[v] = 0;
		}
	}
   // re(i,1,now)
   // 	insert( root,1,now,Q[i].l ,Q[i].r ,Q[i].v ),
   // 	printf("%d %d %d\n",Q[i].l ,Q[i].r ,Q[i].v );
//	re(i,1,tot_l)p(li[i].v );P;
	dfs(1,0,1,q);
	re(i,1,q)
		printf("%d\n",1<<ans[i]);
    return 0;
}

