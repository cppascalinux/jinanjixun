#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define gc() (p1==p2&&(p2=(p1=buffer1)+fread(buffer1,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define pc(x) (p3==p4&&(fwrite(buffer2,1,p3-buffer2,stdout),p3=buffer2,0)?EOF:*p3++=x)
#define flush() (fwrite(buffer2,1,p3-buffer2,stdout),p3=buffer2)
using namespace std;
char *p1,*p2,buffer1[10000009];
char buffer2[10000009],*p3=buffer2,*p4=buffer2+10000000;
int n,m;
int s[1000009];
int tmp[1000009];
template<class T>
void rd(T &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
template<class T>
void output(T x)
{
	pc(x%10+'0');
	if(x)
		output(x/10);
}
int main()
{
	freopen("shinku.in","r",stdin);
	freopen("shinku.out","w",stdout);
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		rd(s[i]);
	for(int i=1,a,b;i<=m;i++)
	{
		rd(a),rd(b);
		int tp=0;
		for(int j=a;j<=b;j++)
			tmp[++tp]=s[j];
		sort(tmp+1,tmp+tp+1);
		tp=unique(tmp+1,tmp+tp+1)-tmp-1;
		int lp=1;
		int ans[11];
		memset(ans,0,sizeof(ans));
		tmp[tp+1]=-1;
		for(int i=1;i<=tp+1;i++)
		{
			if(tmp[i]!=tmp[i-1]+1)
			{
				if(i-lp<=10)
					ans[i-lp]++;
				lp=i;
			}
		}
		for(int i=1;i<=10;i++)
			pc(ans[i]%10+'0');
		pc('\n');
	}
	flush();
	cerr<<clock();
	return 0;
}