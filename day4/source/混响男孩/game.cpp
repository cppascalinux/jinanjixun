#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cstring>
#define ll long long
#define maxn 100005
#define re(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){char c=getchar();int f=1;int ans = 0;while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();}while(c<='9'&&c>='0'){ans =ans*10+c-'0';c=getchar();}return ans*f;}


//_____________________________________________________________________________________________________
int n,m,tot;
int a[maxn],b[maxn];
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int T = read();
	while(T--)
	{
		int n=read(),m=read(); tot = 0;
		a[0]=a[n+1]=0;
		re(i,1,n) a[i] = read()&1;
	//	printf("%d\n",(n+m)&1);
		if(((n+m)&1)==0) printf("A\n");
		else
		{
			int cnt = 0,t=0;
			re(i,1,n+1)
			if(a[i])t++;
			else 
			{
				if((t&1)==0)cnt++;
				t = 0;
			}
		//	printf("%d\n",cnt);
			printf("%c\n",cnt>m?'A':'B');
			
		}
		
	}
    return 0;
}

