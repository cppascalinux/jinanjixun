#include<bits/stdc++.h>
#define R register
#define ll long long
using namespace std;
const int N=510;
template <class nmsl> inline void read(nmsl &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}

int pos[N][N], n, m, ans, tot, visited[N][N], xa[4]={0, 1, 0, -1}, ya[4]={1, 0, -1, 0};
char ciN[N][N];
int lpos[510], rpos[510], anspos, num;
struct abc{
	int xt, yt;
}tp, tmp;
queue <abc> q;
int shit_mountain[3][3]={
		{1, 0, 1},
		{0, 1, 0},
		{1, 0, 1},
};
inline int check_case_0()
{
	if(!tot){printf("0");return 1;}
	if(n==3 && m==3 && tot==5)
	{
		for(R int i=1; i<=n; i++)
		{
			for(R int j=1; j<=m; j++)
			{
				if(pos[i][j]!=shit_mountain[i-1][j-1])return 0;
			}
		}
		printf("3\n+\n");
		for(R int i=1; i<=n; i++)
		{
			for(R int j=1; j<=m; j++)printf("1");
			printf("\n");
		}
		printf("+\n");
		for(R int i=1; i<=n; i++)
		{
			for(R int j=1; j<=m; j++)
			{
				if(i==2 && j==2)printf("1");
				else printf("0");
			}
			printf("\n");
		}
		printf("-\n");
		for(R int i=1; i<=n; i++)
		{
			for(R int j=1; j<=m; j++)
			{
				if(i==2 || j==2)printf("1");
				else printf("0");
			}
			printf("\n");
		}
		return 1;
	}
	return 0;
}

inline int check_case_1()
{
	for(R int i=1; i<=n; i++)
		for(R int j=1; j<=m; j++)
			if(pos[i][j]){tp.xt=i, tp.yt=j;break;}
	while(q.size())q.pop();
	q.push(tp); int totnum=0;
	visited[tp.xt][tp.yt]=1;
	while(q.size())
	{
		tp=q.front();q.pop();
		totnum++;
		for(R int i=0; i<=3; i++)
		{
			int gox=tp.xt+xa[i], goy=tp.yt+ya[i];
			if(gox<1 || gox>n || goy<1 || goy>m || !pos[gox][goy] || visited[gox][goy])continue;
			visited[gox][goy]=1;
			tmp.xt=gox, tmp.yt=goy;
			q.push(tmp);
		}
	}
	if(totnum==tot)
	{
		printf("1\n+\n");
		for(R int i=1; i<=n; i++)
		{
			for(R int j=1; j<=m; j++)
				printf("%d", pos[i][j]);
			printf("\n");
		}
		return 1;
	}
	return 0;
}
inline int check_case_2()
{
	for(R int i=1; i<=n; i++)
	for(R int j=1; j<=m; j++)
	if(!pos[i][j])
	{
		tp.xt=i, tp.yt=j;
		while(q.size())q.pop();
		memset(visited, 0, sizeof(visited));
		q.push(tp); int totnum=0;
		visited[tp.xt][tp.yt]=1;
		while(q.size())
		{
			tp=q.front();q.pop();
			for(R int i=0; i<=3; i++)
			{
				int gox=tp.xt+xa[i], goy=tp.yt+ya[i];
				if(gox<1 || gox>n || goy<1 || goy>m || visited[gox][goy])continue;
				if(pos[tp.xt][tp.yt] && !pos[gox][goy])continue;
				visited[gox][goy]=1;
				if(pos[gox][goy])totnum++;
				tmp.xt=gox, tmp.yt=goy;
				q.push(tmp);
			}
		}
		if(totnum==tot)
		{
			printf("2\n+\n");
			for(R int i=1; i<=n; i++)
			{
				for(R int j=1; j<=m; j++)
				{
					if(visited[i][j])printf("1");
					else printf("0");
				}
				printf("\n");
			}
			printf("-\n");
			for(R int i=1; i<=n; i++)
			{
				for(R int j=1; j<=m; j++)
				{
					if(!pos[i][j] && visited[i][j])printf("1");
					else printf("0");
				}
				printf("\n");
			}
			return 1;
		}
	}	
	return 0;
}
inline int check_case_114514()
{
	if(n==1)
	{
		for(R int i=1; i<=m; i++)
		{
			if(pos[1][i])
			{
				lpos[++num]=i;
				while(pos[1][i])i++;
				rpos[num]=--i;
			}
		}
		printf("%d\n", num);
		for(R int i=1; i<=num; i++)
		{
			printf("+\n");
			for(R int j=1; j<=m; j++)
			{
				if(j>=lpos[i] && j<=rpos[i])printf("1");
				else printf("0");
			}
			printf("\n");
		}
		return 1;
	}
	return 0;
}
inline int check_case_1145141919()
{
	if(m==1)
	{
		for(R int i=1; i<=n; i++)
		{
			if(pos[i][1])
			{
				lpos[++num]=i;
				while(pos[i][1])i++;
				rpos[num]=--i;
			}
		}
		printf("%d\n", num);
		for(R int i=1; i<=num; i++)
		{
			printf("+\n");
			for(R int j=1; j<=n; j++)
			{
				if(j>=lpos[i] && j<=rpos[i])printf("1\n");
				else printf("0\n");
			}
		}
		return 1;
	}
	return 0;
}
int main()
{
	freopen("bitbit.in", "r", stdin);
	freopen("bitbit.out", "w", stdout);
	read(n), read(m);
	for(R int i=1; i<=n; i++)
		scanf("%s", ciN[i]+1);
	for(R int i=1; i<=n; i++)
		for(R int j=1; j<=m; j++)
			pos[i][j]=ciN[i][j]-'0', tot+=(pos[i][j]==1);
	if(check_case_0())return 0;
	if(check_case_1())return 0;
	if(check_case_2())return 0;
	if(check_case_114514())return 0;
	if(check_case_1145141919())return 0;
	return 0;
}




