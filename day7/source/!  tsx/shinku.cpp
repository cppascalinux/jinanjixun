#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<cctype>
using namespace std;
int p1=2000000,p2=2000000,p3=-1;
char buf[5000005],buf2[5000005];
inline int readc()
{
	if(p1>=p2)
	{
		fread(buf,1,p2,stdin);
		p1=0;
	}
	return buf[p1++];
}
inline int read()
{
	int x=0,ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch))
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x;
}
inline void getwr()
{
	fwrite(buf2,1,p3+1,stdout);
	p3=-1;
}
inline void print(int x)
{
	if(x>=10) print(x/10);
	buf2[++p3]=x%10+'0';
	if(p3>=2000000) getwr();
}
struct pt
{
	int l,r,id;
	pt(int l=0,int r=0,int id=0):l(l),r(r),id(id){}
}q[1000005];
struct myarray
{
	vector<int> val;
	vector<pt> tval;
	int fl;
	myarray(){fl=0;val.resize(1000005);}
	int getval(const int x)
	{
		return val[x];
	}
	int& operator [](const int x)
	{
		if(fl) tval.push_back(pt(x,val[x]));
		return val[x];
	}
	void getcr()
	{
		while(!tval.empty())
		{
			pt x=tval[tval.size()-1];
			val[x.l]=x.r;
			tval.pop_back();
		}
	}
}a,vis,tans;
int n,m,b[1000005],bt,fr[1000005],maxn=0;
int f[1000005],sz[1000005],tl,tr,c[1000005];
char tttans[1000005][15];
/*int find(int x)
{
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}
int link(int x,int y)
{
	x=find(x),y=find(y);
	if(x==y) return 0;
	if(sz[x]>sz[y]) f[y]=x;
	else f[x]=y;
	return 1;
}
int check(int x,int y)
{
	return find(x)!=find(y);
}
void ins(int x)
{
	if(!check(x,x+1)) return;
	int szl=sz[find(x)],szr=sz[find(x)+1];
	link(x,x+1);
	int szx=sz[find(x)];
	if(szl<=11) tans[szl]--;
	if(szr<=11) tans[szr]--;
	if(szx<=11) tans[szx]++;
};*/
void getadd(int x)
{
	if(x>10) return;
	int nw=tans.getval(x);
	tans[x]=nw+1;
	//printf("add:x=%d\n",x);
}
void getsub(int x)
{
	if(x>10) return;
	int nw=tans.getval(x);
	tans[x]=nw-1;
	//printf("sub:x=%d\n",x);
}
void ins(int x)
{
	if(vis.getval(x)) return;
	/*printf("ins:x=%d\n",x);
	for(int i=1;i<=maxn;i++)
		printf("%d ",a.getval(i));
	printf("\n");*/
	vis[x]=1;
	int ls=vis.getval(x-1),rs=vis.getval(x+1);
	int lls=a.getval(x-1),rrs=a.getval(x+1);
	if(!ls&&!rs) 
	{
		a[x]=x;
		getadd(1);
	}
	if(ls&&!rs) 
	{
		//printf("---\n");
		a[x]=lls,a[lls]=x;
		getsub(x-lls);
		getadd(x-lls+1);
	}
	if(rs&&!ls)
	{
		//printf("--\n");
		a[x]=rrs,a[rrs]=x;	
		getsub(rrs-x);
		getadd(rrs-x+1);
	}
	if(ls&&rs) 
	{
		int llen=x-1-lls+1,rlen=rrs-(x+1)+1,tlen=rrs-lls+1;
		getsub(llen);
		getsub(rlen);
		getadd(tlen);
		a[lls]=rrs;
		a[rrs]=lls;
	}
}
void tgetcr()
{
	a.getcr();
	vis.getcr();
	tans.getcr();
}
bool cmp(const pt x,const pt y)
{
	return b[x.l]==b[y.l]?x.r<y.r:x.l<y.l;
}
int main()
{
	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		//printf("----------");
		c[i]=read();
		c[i]++;
		maxn=max(maxn,c[i]);
	}
	bt=sqrt(n);
	for(int i=1;i<=n;i++)
	{
		b[i]=(i-1)/bt+1;
		if(!fr[b[i]])
		{
			fr[b[i]]=i;
		}
	}
	fr[b[n]+1]=n+1;
	for(int i=1;i<=m;i++)
	{
		q[i].l=read(),q[i].r=read();
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		a.fl=tans.fl=vis.fl=0;
		if(i==1||b[q[i].l]!=b[q[i-1].l])
		{
			for(int j=1;j<=maxn;j++)
				a[j]=0,vis[j]=0;
			//printf("i=%d",i);
			for(int j=1;j<=11;j++)
				tans[j]=0;
			tl=fr[b[q[i].l]+1];
			tr=tl-1;
		}
		if(b[q[i].l]==b[q[i].r])
		{
			tl=q[i].l;
			tr=tl-1;
			a.fl=tans.fl=vis.fl=1;
			while(tr<q[i].r) ins(c[++tr]);
			for(int j=1;j<=10;j++)
			{
				tttans[q[i].id][j]=tans.getval(j)%10+'0';
				//printf("%d ",tans.getval(j)%10);
			}
			//printf("\n");
			tl=fr[b[q[i].l]+1];
			tr=tl-1;
			tgetcr();
			continue;
		}
		tl=fr[b[q[i].l]+1];
		//printf("q=%d,%d,tl=%d,tr=%d\n",q[i].l,q[i].r,tl,tr);
		while(tr<q[i].r) ins(c[++tr]);
		a.fl=tans.fl=vis.fl=1;
		while(tl>q[i].l) ins(c[--tl]);
		for(int j=1;j<=10;j++)
		{
			tttans[q[i].id][j]=tans.getval(j)%10+'0';
			//printf("%d ",tans.getval(j)%10);
		}
		//printf("\n");
		tgetcr();
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=10;j++)
			buf2[++p3]=tttans[i][j];
		buf2[++p3]='\n';
		if(p3>=2000000) getwr();
	}
	getwr();
	return 0;
}
