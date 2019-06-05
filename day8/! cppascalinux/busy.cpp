#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
#include<ctime>
#include<cmath>
#define inf 0x7F7F7F7F
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m;
int s[100009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void clrv(vector<int> &v)
{
	vector<int> tmp;
	tmp.swap(v);
}
namespace part1
{
	vector<int> v[100009];
	void solve()
	{
		for(int i=1;i<=n;i++)
			v[s[i]].push_back(i);
		int lst=0;
		for(int i=1,a,b,c;i<=m;i++)
		{
			rd(a),rd(b),rd(c);
			b^=lst,c^=lst;
			if(a==1)
			{
				if(b==c)
					continue;
				v[c].insert(v[c].end(),v[b].begin(),v[b].end());
				sort(v[c].begin(),v[c].end());
				clrv(v[b]);
			}
			else
			{
				if(!v[b].size()||!v[c].size())
					lst=0,printf("Chtholly\n");
				else
				{
					if(b==c)
					{
						printf("%d\n",lst=0);
						continue;
					}
					int ans=inf;
					if(v[b].size()>v[c].size())
						swap(b,c);
					for(int i=0;i<(int)v[b].size();i++)
					{
						vector<int>::iterator it1,it2;
						it1=it2=lower_bound(v[c].begin(),v[c].end(),v[b][i]);
						if(it2!=v[c].end())
							ans=min(ans,*it2-v[b][i]);
						if(it1!=v[c].begin())
							ans=min(ans,v[b][i]-*--it1);
					}
					printf("%d\n",lst=ans);
				}
			}
		}
	}
}
namespace part2
{
	int l,tp=0;
	vector<int> v[100009];
	int pos[100009];
	int bst[1009];
	int bas[1009][1009];
	void init()
	{
		l=sqrt(n);
		for(int i=1;i<=100000;i++)
			if(v[i].size()>=l)
				bst[++tp]=i,pos[i]=tp;
		// printf("tp:%d\n",tp),fflush(stdout);
		for(int i=1;i<=tp;i++)
		{
			for(int j=i+1;j<=tp;j++)
			{
				int a=bst[i],b=bst[j];
				if(v[a].size()>v[b].size())
					swap(a,b);
				int ans=inf;
				for(int k=0;k<(int)v[a].size();k++)
				{
					vector<int>::iterator it1,it2;
					it1=it2=lower_bound(v[b].begin(),v[b].end(),v[a][k]);
					if(it2!=v[b].end())
						ans=min(ans,*it2-v[a][k]);
					if(it1!=v[b].begin())
						ans=min(ans,v[a][k]-*--it1);
				}
				bas[i][j]=bas[j][i]=ans;
			}
		}
	}
	void solve()
	{
		for(int i=1;i<=n;i++)
			v[s[i]].push_back(i);
		// init();
		int lst=0;
		for(int i=1,a,b,c;i<=m;i++)
		{
			rd(a),rd(b),rd(c);
			b^=lst,c^=lst;
			if(!v[b].size()||!v[c].size())
				lst=0,printf("Chtholly\n");
			else
			{
				if(b==c)
				{
					printf("%d\n",lst=0);
					continue;
				}
				int nb=v[b].size()>=l;
				int nc=v[c].size()>=l;
				if(nb&&nc&&0)
					printf("%d\n",lst=bas[pos[b]][pos[c]]);
				else
				{
					int ans=inf;
					if(v[b].size()>v[c].size())
						swap(b,c);
					for(int i=0;i<(int)v[b].size();i++)
					{
						vector<int>::iterator it1,it2;
						it1=it2=lower_bound(v[c].begin(),v[c].end(),v[b][i]);
						if(it2!=v[c].end())
							ans=min(ans,*it2-v[b][i]);
						if(it1!=v[c].begin())
							ans=min(ans,v[b][i]-*--it1);
					}
					printf("%d\n",lst=ans);
				}
			}
		}
	}
}
int main()
{
	freopen("busy.in","r",stdin);
	freopen("busy.out","w",stdout);
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		rd(s[i]);
	// if(n<=1000)
		part1::solve();
	// else
		// part2::solve();
	cerr<<clock();
	return 0;
}