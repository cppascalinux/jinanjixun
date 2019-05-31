#include<cstdio>
#include<cstring>
#define N 510
int dep[N],son[N][2],V[N],M,Rt,fa[N];
void insert(int &x,int y,int i,int F)
{
	if (!x) {dep[i]=dep[F]+1;fa[i]=F;x=i;return;}
	if (V[x]>y) insert(son[x][0],y,i,x);
	else insert(son[x][1],y,i,x);
}
int main()
{
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	int T,a,b,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&a,&b,&M,&n);
		memset(dep,0,sizeof(dep));
		memset(son,0,sizeof(son));
		memset(fa,0,sizeof(fa));
		Rt=0;dep[0]=-1;
		for (int i=1;i<=n;++i) insert(Rt,V[i]=(a+1ll*b*i)%M,i,0);
		printf("%d\n",dep[n]);
	}
	return 0;
}

//by qlwpc
