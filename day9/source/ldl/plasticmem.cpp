#include<iostream>
#include<cstdio>
using namespace std;
int n,m,ans,a[2002019];
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main()
{
	freopen("plasticmem.in","r",stdin);
	freopen("plasticmem.out","w",stdout);
	n=read(); m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int opt=read(),l=read(),r=read();
		switch(opt){
			case 1: for(int i=l;i<=r;i++)a[i]=0; break;
			case 2: for(int i=l;i<=r;i++)a[i]=1; break;
			case 3: for(int i=l;i<r;i++)a[i]|=a[i+1]; break;
			case 4: for(int i=r;i>l;i--)a[i]|=a[i-1]; break;
			case 5: for(int i=l;i<r;i++)a[i]&=a[i+1]; break;
			case 6: for(int i=r;i>l;i--)a[i]&=a[i-1]; break;
			case 7: for(int i=l;i<=r;i++)ans+=a[i]; printf("%d\n",ans); ans=0; break;
		}
	}fclose(stdin); fclose(stdout);
	return 0;
}
