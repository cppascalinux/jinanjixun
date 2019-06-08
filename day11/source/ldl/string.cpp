#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2002018
using namespace std;
int k,n,m,q;char s[N];
int sa[N],c[N],y[N],x[N];
void get_SA(){
    for(int i=1;i<=n;i++)++c[x[i]=s[i]];
    for(int i=2;i<=m;i++)c[i]+=c[i-1];
    for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k<<=1){
        int num=0;
        for(int i=n-k+1;i<=n;i++)y[++num]=i;//y[i]表示第二关键字排名为i的字符第一关键字的下标 
        for(int i=1;i<=n;i++)if(sa[i]>k)y[++num]=sa[i]-k;
        for(int i=1;i<=m;i++)c[i]=0;
        for(int i=1;i<=num;i++)++c[x[i]];
        for(int i=2;i<=m;i++)c[i]+=c[i-1];
        for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i],y[i]=0;
        swap(x,y);x[sa[1]]=1;num=1;
        for(int i=2;i<=n;i++)x[sa[i]]=(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k])?num:++num;
        if(m=num,num==n)break;
    }
}
int get(int x){
	int res=0;
	for(;x;x>>=1)res+=x&1;
	return res;
}
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	cin>>k>>q; n=(1<<k);
	for(int i=0;i<n;i++)
		s[i+1]=get(i)%2+'a';
    m='b';
    get_SA();//sa[i]表示排名为i的字符的下标 
    while(q--){
    	int a;cin>>a;cout<<sa[a]-1<<" ";
    }fclose(stdin); fclose(stdout);
    return 0;
}
