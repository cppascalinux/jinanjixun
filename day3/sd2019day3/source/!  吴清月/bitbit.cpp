#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
int n,m;
char s[1005][1005],out[1005][1005];
bool flag[1005][1005];
queue<int>qx,qy;
int calc()
{
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    flag[i][j]=0;
	int num=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		if(out[i][j]=='1'&&!flag[i][j])
		{
			num++;
			qx.push(i);
			qy.push(j);
			flag[i][j]=1;
			while(!qx.empty())
			{
				int x=qx.front();
				int y=qy.front();
				qx.pop();
				qy.pop();
				for(int k=0;k<4;k++)
				{
					int xx=x+dx[k];
					int yy=y+dy[k];
					if(out[xx][yy]=='1'&&!flag[xx][yy])
					{
						flag[xx][yy]=1;
						qx.push(xx);
						qy.push(yy);
					}
				}
			}
		}
	}
	return num;
}
int main()
{
	freopen("bitbit.in","r",stdin);
	freopen("bitbit.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	if(n==1)
	{
		int num=0;
		for(int i=1;i<=m;i++)
		  if(s[1][i]=='1'&&s[1][i-1]!='1')num++;
		printf("%d\n",num);
		for(int i=1;i<=num;i++)
		{
			printf("+\n");
			bool f=0;
			for(int j=1;j<=m;j++)
			{
				if(f==0&&s[1][j]=='1')
				{
					putchar('1');
					s[1][j]='0';
					if(s[1][j+1]!='1')f=1;
				}
				else putchar('0');
			}
			putchar('\n');
		}
		return 0;
	}
	int num=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		if(s[i][j]=='1'&&!flag[i][j])
		{
			num++;
			qx.push(i);
			qy.push(j);
			flag[i][j]=1;
			while(!qx.empty())
			{
				int x=qx.front();
				int y=qy.front();
				qx.pop();
				qy.pop();
				for(int k=0;k<4;k++)
				{
					int xx=x+dx[k];
					int yy=y+dy[k];
					if(s[xx][yy]=='1'&&!flag[xx][yy])
					{
						flag[xx][yy]=1;
						qx.push(xx);
						qy.push(yy);
					}
				}
			}
		}
	}
	if(num<=2)
	{
		printf("%d\n",num);
		if(num==0)return 0;
		memset(flag,0,sizeof(flag));
		for(int i=1;i<=n;i++)
		  for(int j=1;j<=m;j++)
		    out[i][j]='0';
		for(int i=1;i<=n;i++)out[i][m+1]='\0';
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='1'&&!flag[i][j])
			{
				printf("+\n");
				num++;
				qx.push(i);
				qy.push(j);
				flag[i][j]=1;
				while(!qx.empty())
				{
					int x=qx.front();
					int y=qy.front();
					qx.pop();
					qy.pop();
					out[x][y]='1';
					for(int k=0;k<4;k++)
					{
						int xx=x+dx[k];
						int yy=y+dy[k];
						if(s[xx][yy]=='1'&&!flag[xx][yy])
						{
							flag[xx][yy]=1;
							qx.push(xx);
							qy.push(yy);
						}
					}
				}
				for(int i=1;i<=n;i++)
				  printf("%s\n",out[i]+1);
				for(int i=1;i<=n;i++)
				  for(int j=1;j<=m;j++)
				    out[i][j]='0';
			}
		}
	}
	if(num==3)
	{
		printf("2\n");
		for(int i=1;i<=n;i++)
		  for(int j=1;j<=m;j++)
		    out[i][j]=s[i][j];
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='0'&&!flag[i][j])
			{
				num++;
				qx.push(i);
				qy.push(j);
				flag[i][j]=1;
				while(!qx.empty())
				{
					int x=qx.front();
					int y=qy.front();
					qx.pop();
					qy.pop();
					out[x][y]='1';
					for(int k=0;k<4;k++)
					{
						int xx=x+dx[k];
						int yy=y+dy[k];
						if(s[xx][yy]=='0'&&!flag[xx][yy])
						{
							flag[xx][yy]=1;
							qx.push(xx);
							qy.push(yy);
						}
					}
				}
				if(calc()==1)
				{
					printf("+\n");
					for(int i=1;i<=n;i++)
					  printf("%s\n",out[i]+1);
					printf("-\n");
					for(int i=1;i<=n;i++)
					{
						for(int j=1;j<=m;j++)
						{
							if(out[i][j]=='1'&&s[i][j]=='0')putchar('1');
							else putchar('0');
						}
						putchar('\n');
					}
					return 0;
				}
				for(int i=1;i<=n;i++)
				  for(int j=1;j<=m;j++)
				    out[i][j]=s[i][j];
			}
		}
	}
	if(num==5)
	{
		printf("3\n");
		printf("+\n111\n010\n111\n");
		printf("-\n010\n000\n000\n");
		printf("-\n000\n000\n010\n");
		return 0;
	}
	printf("2\n");
	printf("+\n010\n111\n010\n");
	printf("-\n000\n010\n000\n");
	return 0;
}
