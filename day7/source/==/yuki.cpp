#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<queue>
#define M 3000001
#define Re register
using namespace std;

int i,m,n,j,k,dfn[M],f[M],wson[M],top[M],cnt,d[M];
int head[M],nex[M],ver[M],size[M],q,lazy[M],rt[M],x,y,opt,val[M];
queue <int> Q;

struct io
{
	char ibuf[20<<22] , * s , obuf[20<<22] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen("yuki.in","r",stdin);
		freopen("yuki.out","w",stdout);
		fread( s = ibuf , 1 , 10<<22 , stdin );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	inline int read()
	{
		register int u = 0;
		while( * s < 48 ) s++;
		while( * s > 32 )
			u = u * 10 + * s++ - 48;
		return u;
	}
	template < class T >
	inline void print( register T u )
	{
		static int * q = a;
		if( !u ) * t++ = 48;
		else
		{
			while( u ) * q++ = u % 10 + 48 , u /= 10;
			while( q != a )
				* t++ = * --q;
		}
		* t++ = '\n';
	}
} ip;

inline void add(int x,int y)
{
    ver[++cnt]=y, nex[cnt]=head[x], head[x]=cnt;
	ver[++cnt]=x, nex[cnt]=head[y], head[y]=cnt;
}

struct treap
{
	int c[M][2],s[M],tot[M],rnd[M],val[M],w,cnt,op;
	inline int Nw(int x)
	{
		Re int w;
		if(Q.size()) w=Q.front(), Q.pop();
	    else w=++cnt;
	    c[w][0]=c[w][1]=0;
	    tot[w]=s[w]=1;
	    val[w]=x; 
	    rnd[w]=rand();
	    return w;
	}
	
	inline void update(int x)
	{
	    if(x) s[x]=s[c[x][0]]+s[c[x][1]]+tot[x];
	}
	
	void split(int now,int k,int &x,int &y)
	{
	    if(!now)  x=y=0;
	    else 
	    {
	        if(val[now]<=k) x=now, split(c[now][1],k,c[now][1],y);
	        else y=now, split(c[now][0],k,x,c[now][0]);
	        update(now);
	    }
	}
	
	int mrg(int x,int y)
	{
	    if(!x || !y) return x+y;
	    if(rnd[x]<rnd[y]) {c[x][1]=mrg(c[x][1],y); update(x); return x;}
	    else {c[y][0]=mrg(x,c[y][0]);  update(y); return y;}
	}
	
	int fnd(int x,int k)
	{
	    while(1)
	    {
	        if(s[c[x][0]]>=k) x=c[x][0];
	        else if(s[c[x][0]]+tot[x]>=k) return val[x];
	        else k-=s[c[x][0]]+tot[x],x=c[x][1] ;
	    }
	}
	
	void ins(int &root,int k)
	{
	    Re int x=0,y=0,z=0;
	    split(root,k,x,y);
	    split(x,k-1,x,z);
	    if(z) s[z]++, tot[z]++;
	    else z=Nw(k);
	    x=mrg(x,z);
	    root=mrg(x,y);
	}
	
	void del(int &root,int k)
	{
	    Re int x=0,y=0,z=0;
	    split(root,k,x,y);
	    split(x,k-1,x,z);
	    if(tot[z]>1) {tot[z]--,s[z]--; x=mrg(x,z);} 
	    else Q.push(z);
	    root=mrg(x,y);
	}
} T1;

inline void down(int now)
{
    lazy[now*2]+=lazy[now];
    lazy[now*2+1]+=lazy[now];
    lazy[now]=0;
}

void dfs1(int now)
{

    size[now]=1;
    for(Re int i=head[now];i;i=nex[i])
    {
    	if(size[ver[i]]) continue;
        Re int t=ver[i];
        f[t]=now;
        d[t]=d[now]+1;
        dfs1(t);
        size[now]+=size[t];
        if(size[t]>size[wson[now]]) wson[now]=t;
    }
}

void dfs2(int now,int fa)
{
    dfn[now]=++cnt;  top[now]=fa;
    if(wson[now]) dfs2(wson[now],fa);
    for(int i=head[now];i;i=nex[i])
    {
        Re int t=ver[i];
        if(dfn[ver[i]]) continue;
        T1.ins(rt[now],val[ver[i]]);
        dfs2(t,t);
    }
}

inline void mody(int x,int k)
{
	for(Re int i=x;i<=n;i+=i&-i) lazy[i]+=k; 
}

inline int sum(int x)
{
	Re int sum=0;
	for(Re int i=x;i>0;i-=i&-i) sum+=lazy[i];
	return sum;
}

inline void ad(int ll,int rr,int k)
{
	mody(ll,k);
	mody(rr+1,-k);
}

int qsum(int l,int r,int k)
{
    int ans=0;
    while(top[l]!=top[r])
    {
        if(d[top[l]]>d[top[r]]) swap(l,r);
        if(f[top[r]])T1.del(rt[f[top[r]]],sum(dfn[top[r]]));
        if(f[top[r]])T1.ins(rt[f[top[r]]],sum(dfn[top[r]])+k);
        ad(dfn[top[r]],dfn[r],k);
        
        r=f[top[r]];
    }
    if(d[l]>d[r]) swap(l,r);
    if(l==top[r]) 
    {
    	if(f[top[r]])T1.del(rt[f[top[r]]],sum(dfn[top[r]]));
        if(f[top[r]])T1.ins(rt[f[top[r]]],sum(dfn[top[r]])+k);
	}
    ad(dfn[l],dfn[r],k);
    return ans;
}


int main()
{
	srand(time(0));
	n=ip.read(), m=ip.read();
    for(Re int i=1;i<=n;i++) val[i]=ip.read();
    
    for(Re int i=1;i<n;i++)
    {
    	x=ip.read(), y=ip.read();
    	add(x,y);
	}
	cnt=0;
	dfs1(1);
	dfs2(1,0);
	for(Re int i=1;i<=n;i++) ad(dfn[i],dfn[i],val[i]);
	int ct=0;
	for(Re int i=1;i<=m;i++)
	{
		opt=ip.read() ,x=ip.read() ,y=ip.read();
		if(opt==2) 
		{
			T1.ins(rt[x],sum(dfn[x]));
			if(f[x])T1.ins(rt[x],sum(dfn[f[x]]));
			if(wson[x])T1.ins(rt[x],sum(dfn[wson[x]]));
			ip.print(T1.fnd(rt[x],y));
			//putchar(10);
			T1.del(rt[x],sum(dfn[x]));
			if(f[x])T1.del(rt[x],sum(dfn[f[x]]));
			if(wson[x])T1.del(rt[x],sum(dfn[wson[x]]));
		}
		else
		{
			k=ip.read();
			qsum(x,y,k);
		}
			
	}
	return 0;
}
