#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define gc() (p1==p2&&(p2=(p1=buffer1)+fread(buffer1,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define pc(x) (p3==p4&&(fwrite(buffer2,1,p3-buffer2,stdout),p3=buffer2,0)?EOF:*p3++=x)
#define flush() (fwrite(buffer2,1,p3-buffer2,stdout),p3=buffer2)
using namespace std;
char *p1,*p2,buffer1[10000009];
char buffer2[10000009],*p3=buffer2,*p4=buffer2+10000000;
int n,m,tot;
int hd[1000009],eg[2000009],nxt[2000009];
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
	freopen("yuki.in","r",stdin);
	freopen("yuki.out","w",stdout);
	scanf("%d%d",&n,&m);

	return 0;
}