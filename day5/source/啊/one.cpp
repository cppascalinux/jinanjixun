#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define LL long long 
using namespace std;
const int P = 1e9+7;
const int N = 370502329;
const int bas= 233;
const int M = 100001;

int res,n,m,k,a[M],vis[M],b[M],fn,cnt,ct,c[M],d[650][650],B,K;
map<int,int> mp;
int hs()
{
	LL z=0;
	for(int i=1;i<=n;i++) z=(z*bas+b[i])%N;
	return z;
}

int qick(LL a,LL b)
{
	LL z=1;
	for(;b;b>>=1, a=a*a%P) if(b&1)z=z*a%P;
	return z;
}

void md()
{
	if(b[1]==n) return;
	int k=mp[hs()];
	for(int i=n;i>=2;i--) if(b[i])
		for(int j=i-1;j>=1 && i-j<=j ;j--) 
		{
			b[i]--; b[j]++; b[i-j]++;
			int w=mp[hs()];
			b[i]++; b[j]--; b[i-j]--;
			if(w==cnt) continue;
			if(i-j!=j)d[w][k]=(LL)i*b[i]*K%P;
			else d[w][k]=(LL)i*b[i]*K*(P+1)/2%P;
		}
	for(int i=1;i<=n;i++) if(b[i])
		for(int j=i;j<=n && j+i<=n; j++) if(b[j])
		{
			b[i]--; b[j]--; b[i+j]++;
			int w=mp[hs()];
			b[i]++; b[j]++; b[i+j]--;
			if(w==cnt) continue;
			if(i==j) d[w][k]=(LL)i*i*(b[i]*(b[i]-1))/2*K%P;
			else d[w][k]=(LL)i*j*b[i]*b[j]*K%P;
		}

	d[k][k]=P-1;
}

void dfs(int x,int k)
{
	if(!x) 
	{
		
		if(!B)
		{
			if(b[1]==n) return ;
			//if(b[1]==n) fn=cnt+1;
			mp[hs()]=++cnt;
		}
		else if(mp[hs()]!=cnt)md();
		return ;	
	}
	for(int i=k;i>=1;i--)if(x>=i)
	{
		b[i]++;
		dfs(x-i,i);
		b[i]--;
	}

}

void fnd(int x)
{
	if(vis[x]) return;
	ct++;
	vis[x]=1;
	fnd(a[x]);
}

void Gauss()
{
    int r; int db;
    for(int i=1;i<=cnt;i++)
    {
        for(r=i;r<=cnt;r++) if(d[r][i]) break;
        if(r!=i) swap(d[r],d[i]);
        for(int j=i+1;j<=cnt;j++)
        {
            db=(LL)d[j][i]*qick(d[i][i],P-2)%P;
            for(int l=i;l<=cnt+1;l++) d[j][l]=((LL)d[j][l]-(LL)db*d[i][l]%P+P)%P;
        }
    }
    for(int i=cnt;i>0;i--)
    {
        for(int j=i+1;j<cnt;j++) d[i][cnt+1]=(d[i][cnt+1]-(LL)d[j][cnt+1]*d[i][j]%P+P)%P;
        d[i][cnt+1]=(LL)d[i][cnt+1]*qick(d[i][i],P-2)%P;
    }
}


int main()
{
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	scanf("%d",&n);
	dfs(n,n);
	K=qick(n*(n-1)/2,P-2);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	memset(b,0,sizeof(b)); B=1;
	b[1]=n; mp[hs()]=++cnt; b[1]=0;
	dfs(n,n);
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;i++) if(!vis[i])
	{
		ct=0;
		fnd(i);
		b[ct]++;
	}
	if(b[1]==n) 
	{
		printf("0\n");
		return 0;
	}
	d[mp[hs()]][cnt+1]=P-1;
	//d[cnt][cnt]=P-1;
//	for(int i=1;i<cnt;i++)
//		for(int j=1;j<cnt;j++) if(i!=j)
//			d[i][cnt+1]=(d[i][cnt+1]+P-d[i][j])%P;
	Gauss();
	for(int i=1;i<cnt;i++) res=(res+d[i][cnt+1])%P;
	printf("%d",res);
}