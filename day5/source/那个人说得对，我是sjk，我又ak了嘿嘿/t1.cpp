#include<map>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int INF=1000000007,N=666;
int a[N][N],w[N],ans[N];
map<vector<int>,int>mp2;
map<int,vector<int> >mp;
vector<int>s,v,vec,ss;
int cnt,all,n,vis[N];
int ksm(int w,int x)
{
	int ans=1;
	while(x)
	{
		if(x&1)
			ans=(long long)ans*w%INF;
		x>>=1;
		w=(long long)w*w%INF;
	}
	return ans;
}
void dfs(int x,int mx,int val)
{
	int i;
	if(n==val)
	{
		cnt++;
		mp[cnt]=vec;
		mp2[vec]=cnt;
		if(vec.size()==n)
			vis[cnt]=1;
		return;
	}
	for(i=mx;i<=n-val;i++)
	{
		vec.push_back(i);
		dfs(x+1,i,val+i);
		vec.pop_back();
	}
}
int zl(vector<int>s)
{
	int i;
	v.clear();
	for(i=0;i<s.size();i++)
		if(s[i])
			v.push_back(s[i]);
	sort(v.begin(),v.end());
	return mp2[v];
}
void build()
{
	int i,j,now,gl,nw,k;
	for(i=1;i<=cnt;i++)
	{
		a[i][i]=INF-1;
		if(vis[i]==1)
			continue;
		s=mp[i];
		now=1;
		for(j=0;j<s.size();j++)
		{
			for(k=j+1;k<s.size();k++)
			{
				ss=s;
				gl=(long long)s[j]*s[k]%INF*ksm(all,INF-2)%INF;
				ss[j]=s[j]+s[k];
				ss[k]=0;
				nw=zl(ss);
				a[i][nw]=(a[i][nw]+gl)%INF;
			}
		}
		for(j=0;j<s.size();j++)
		{
			ss=s;
			for(k=1;k<=s[j]/2;k++)
			{
				ss=s;
				ss.push_back(k);
				ss[j]=s[j]-k;
				nw=zl(ss);
//				if(i==4&&nw==4)
//					printf("%d %d\n",s[i]
				if(s[j]-k!=k)
					gl=s[j];
				else
					gl=s[j]/2;
				gl=(long long)gl*ksm(all,INF-2)%INF;
				a[i][nw]=(a[i][nw]+gl)%INF;
			}
		}
//		printf("*");
		a[i][cnt+1]=INF-1;
	}
//				printf("%d %d %d\n",i,j,k);
}
void gauss(int n)
{
    int now,i,j,k;
    int tmp;
    now=1;
    for(i=1;i<=n;i++)
    {
        if(a[i][now]==0)
        {
            for(j=i;j<=n;j++)
                if(a[j][now]!=0)
                    break;
            if(j<=n)
                for(k=now;k<=n+1;k++)
                    swap(a[i][k],a[j][k]);
        }
        for(j=i+1;j<=n;j++)
        {
            tmp=(long long)a[j][now]*ksm(a[i][now],INF-2)%INF;
            for(k=now+1;k<=n+1;k++)
                a[j][k]=(a[j][k]-(long long)tmp*a[i][k]%INF+INF)%INF;
            a[j][now]=0;
        }
        now++;
    }
    for(i=n;i>=1;i--)
    {
        ans[i]=(long long)a[i][n+1]*ksm(a[i][i],INF-2)%INF;
        for(j=i-1;j;j--)
            a[j][n+1]=(a[j][n+1]-(long long)ans[i]*a[j][i]%INF+INF)%INF;
    }
}
int main()
{
	int i,cntt=0,tmp,nw;
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	scanf("%d",&n);
	all=(long long)n*(n-1)/2;
	dfs(1,1,0);
	for(i=1;i<=n;i++)
		scanf("%d",&w[i]);
	build();
//	for(i=1;i<=cnt;i++)
//	{
//		for(int j=1;j<=cnt+1;j++)
//			printf("%d ",a[i][j]);
//		puts("");
//	}
	gauss(cnt);
	s.clear();
	memset(vis,0,sizeof(vis));
	for(i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			cntt=0;
			tmp=i;
			while(1)
			{
				cntt++;
				tmp=w[tmp];
				vis[tmp]=1;
				if(tmp==i)
					break;
			}
//			printf("%d\n",cntt);
			s.push_back(cntt);
		}
	}
	nw=zl(s); 
//	printf("%d\n",nw);
	printf("%d\n",ans[nw]);
	return 0;
}

