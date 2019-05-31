#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=505;
int dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
int n,m,cnt,cnt1,cntt,sw,sum;
int a[N][N],b[N][N],as[N][N],fa[N*N],sz[N*N],vis[N][N],L[N],R[N];
pair<int,int> g[N*N],q[N*N];
void change(int a[N][N])
{
	int i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			b[i][j]=a[i][j];
	memset(a,0,sizeof(a));
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
			a[i][j]=b[j][i];

}
void out()
{
	int i,j;
	if(sw==1)
	{
		change(as);
		swap(n,m);
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
			printf("%d ",as[i][j]);
		puts("");
	}
	if(sw==1)
	{
		change(as);
		swap(n,m);
	}
}
int check0()
{
	if(sum==0)
	{
		puts("0");
		return 1;
	}
	return 0;
}
int check1()
{
	int h,t,i,j,x,y,nx,ny;
	h=t=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if(a[i][j]==1)
			{
				q[t++]=make_pair(i,j);
				vis[i][j]=1;
				break;
			}
		}
		if(j<=m)
			break;
	}
	while(h<t)
	{
		x=q[h].first,y=q[h].second;
		h++;
		for(i=0;i<4;i++)
		{
			nx=x+dx[i],ny=y+dy[i];
			if(nx<=0||nx>n||ny<=0||ny>m||vis[nx][ny]||!a[nx][ny])
				continue;
			vis[nx][ny]=1;
			q[t++]=make_pair(nx,ny);
		}
	}
//	printf("%d %d\n",h,sum);
	if(h==sum)
	{
		puts("1");
		for(i=0;i<h;i++)
			as[q[i].first][q[i].second]=1;
		puts("+");
		out();
		return 1;
	}
	return 0;
}
int gao1()
{
	memset(as,0,sizeof(as));
	int h,t,i,j,x,y,nx,ny,tmp;
	h=t=0;
	memset(vis,0,sizeof(vis));
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if(a[i][j]==1)
			{
				q[t++]=make_pair(i,j);
				vis[i][j]=1;
				break;
			}
		}
		if(j<=m)
			break;
	}
	while(h<t)
	{
		x=q[h].first,y=q[h].second;
		h++;
		for(i=0;i<4;i++)
		{
			nx=x+dx[i],ny=y+dy[i];
			if(nx<=0||nx>n||ny<=0||ny>m||vis[nx][ny]||!a[nx][ny])
				continue;
			vis[nx][ny]=1;
			q[t++]=make_pair(nx,ny);
		}
	}
	tmp=h;
	for(i=0;i<h;i++)
		as[q[i].first][q[i].second]=1;
	h=t=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if(a[i][j]==1&&vis[i][j]==0)
			{
				q[t++]=make_pair(i,j);
				vis[i][j]=1;
				break;
			}
		}
		if(j<=m)
			break;
	}
	while(h<t)
	{
		x=q[h].first,y=q[h].second;
		h++;
		for(i=0;i<4;i++)
		{
			nx=x+dx[i],ny=y+dy[i];
			if(nx<=0||nx>n||ny<=0||ny>m||vis[nx][ny]||!a[nx][ny])
				continue;
			vis[nx][ny]=1;
			q[t++]=make_pair(nx,ny);
		}
	}
//	printf("%d %d %d\n",tmp,h,sum);
	if(tmp+h==sum)
	{
		puts("2");
		puts("+");
		out();
		memset(as,0,sizeof(as));
		for(i=0;i<h;i++)
			as[q[i].first][q[i].second]=1;
		puts("+");
		out();
		return 1;
	}
	memset(as,0,sizeof(as));
	return 0;
}
int calc(int x,int y)
{
	return (x-1)*n+y;
}
int find_set(int x)
{
	if(fa[x]==x)
		return x;
	return find_set(fa[x]);
}
void merge(int x,int y)
{
	int xx=find_set(x),yy=find_set(y);
	if(xx==yy)
		return;
	if(sz[xx]>sz[yy])
		swap(xx,yy);
	fa[xx]=yy,sz[yy]+=sz[xx];
	g[++cnt1]=make_pair(xx,yy);
//	printf("%d %d %d %d\n",xx,yy,sz[xx],sz[yy]);
}
int gao(int X,int Y)
{
	int h,t,x,y,nx,ny,i,j,xx,yy;
	h=t=0;
	q[t++]=make_pair(X,Y);
	vis[X][Y]=1;
	while(h<t)
	{
		x=q[h].first,y=q[h].second;
		h++;
		for(i=0;i<4;i++)
		{
			nx=x+dx[i],ny=y+dy[i];
			if(nx<=0||nx>n||ny<=0||ny>m||vis[nx][ny]||a[nx][ny])
				continue;
			vis[nx][ny]=1;
			q[t++]=make_pair(nx,ny);
		}
	}
	cnt1=0;
	for(i=0;i<h;i++)
	{
		x=q[i].first,y=q[i].second;
		as[x][y]=1;
		a[x][y]=1;
		for(j=0;j<4;j++)
		{
			nx=x+dx[j],ny=y+dy[j];
			if(nx<=0||nx>n||ny<=0||ny>m)
				continue;
			if(a[nx][ny])
				merge(calc(x,y),calc(nx,ny));
		}
	}
//	printf("%d\n",a[1][4]);
//	printf("%d %d %d %d %d %d\n",X,Y,h,sum,sz[find_set(calc(x,y))],cnt1);
//	out()
	if(sz[find_set(calc(x,y))]-h==sum)
	{
		puts("2");
		puts("-");
		out();
		puts("+");
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				as[i][j]=a[i][j];
		out();
		return 1;
	}
	for(i=cnt1;i>=1;i--)
	{
		xx=g[i].first,yy=g[i].second;
		sz[yy]-=sz[xx],fa[xx]=xx;
//		printf("%d %d %d %d\n",xx,yy,sz[xx],sz[yy]);
	}
	for(i=0;i<h;i++)
	{
		x=q[i].first,y=q[i].second;
		a[x][y]=as[x][y]=0;
	}
	return 0;
}
int gao2()
{
	int i,x,y,nx,ny,X,Y;
	for(i=1;i<=n*m;i++)
		fa[i]=i,sz[i]=1;
	for(x=1;x<=n;x++)
		for(y=1;y<=m;y++)
		{
			if(a[x][y])
			{
				for(i=0;i<4;i++)
				{
					nx=x+dx[i],ny=y+dy[i];
					if(nx<=0||nx>n||ny<=0||ny>m)
						continue;
					if(a[nx][ny])
						merge(calc(x,y),calc(nx,ny));
				}
			}
		}
	memset(vis,0,sizeof(vis));
	for(X=1;X<=n;X++)
	{
		for(Y=1;Y<=m;Y++)
		{
			if(vis[X][Y]==0&&a[X][Y]==0)
			{
				if(gao(X,Y))
				{
					return 1;
				}
			}
		}
	}
	return 0;
}
int check2()
{
	if(gao1())
		return 1;
	if(gao2())
		return 1;
}
char aa[N];
int main()
{
	int i,j,pl,lst;
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%s",aa+1);
		for(j=1;j<=m;j++)
		{
			a[i][j]=aa[j]-'0';
			sum+=a[i][j];
		}
	}
	if(n>m)
	{
		change(a);
		sw=1;
		swap(n,m);
	}
	if(check0())
	{
		return 0;
	}
	if(n==1)
	{
		pl=1;
		lst=1;
		a[1][m+1]=0;
		while(pl<=m+1)
		{
			if(a[1][pl]==1)
				pl++;
			else
			{
				if(lst!=pl)
					cntt++,L[cntt]=lst,R[cntt]=pl-1;
				lst=pl+1;
				pl++;
			}
		}
		printf("%d\n",cntt);
		for(i=1;i<=cntt;i++)
		{
			for(j=L[i];j<=R[i];j++)
				as[1][j]=1;
			puts("+");
			out();
			for(j=L[i];j<=R[i];j++)
				as[1][j]=0;
		}
		return 0;
	}
	if(check1())
	{
		return 0;
	}
	if(check2())
	{
		return 0;
	}
	puts("3");
//	if(m==2)
//	{
//		change(a);
//		swap(n,m);
//		sw^=1;
//	}
	for(i=1;i<=n;i+=2)
	{
		for(j=1;j<m;j++)
			as[i][j]=1;
	}
	for(i=2;i<=n;i+=2)
	{
		as[i][1]=1;
		for(j=2;j<m;j++)
		{
			as[i][j]=a[i][j];
		}
	}
	puts("+");
	out();
	memset(as,0,sizeof(as));
	
	for(i=2;i<=n;i+=2)
	{
		for(j=2;j<=m;j++)
			as[i][j]=1;
	}
	for(i=1;i<=n;i+=2)
	{
		as[i][m]=1;
		for(j=2;j<m;j++)
		{
			as[i][j]=a[i][j];
		}
	}
	puts("+");
	out();
	memset(as,0,sizeof(as));
	for(i=1;i<=n;i++)
	{
		if(a[i][1]==1)
			as[i][1]=0;
		else
			as[i][1]=1;
		if(a[i][m]==1)
			as[i][m]=0;
		else
			as[i][m]=1;
		for(j=2;j<m;j++)
			as[i][j]=1;
	}
	puts("-");
	out();
	return 0;
}

