#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
using namespace std;
int m,n;
int l[30009],r[30009],v[60009];
int c1[30009],c2[30009];
int s[30009];
void init()
{
	n=0;
	for(int i=1;i<=m;i++)
		v[++n]=l[i],v[++n]=r[i];
	sort(v+1,v+n+1);
	n=unique(v+1,v+n+1)-v-1;
	for(int i=1;i<=m;i++)
	{
		l[i]=lower_bound(v+1,v+n+1,l[i])-v;
		r[i]=lower_bound(v+1,v+n+1,r[i])-v;
	}
	n++;
}
int solve()
{
	for(int i=1;i<=m;i++)
		if(c2[i])
			s[l[i]]++,s[r[i]+1]--;
		else
			s[l[i]]--,s[r[i]+1]++;
	for(int i=1;i<=n;i++)
	{
		s[i]+=s[i-1];
		if(abs(s[i])>1)
			return 0;
	}
	return 1;
}
int main()
{
	for(int i=1;i<=50;i++)
	{
		char sin[20],sans[20],scmd[20];
		sprintf(scmd,"cp b%d.in wait.in",i);
		system(scmd);
		system("wait.exe");
		sprintf(sin,"b%d.in",i);
		sprintf(sans,"b%d.out",i);
		FILE *in=fopen(sin,"r"),*ans=fopen(sans,"r"),*out=fopen("wait.out","r");
		fscanf(in,"%d%d",&m,&n);
		for(int i=1;i<=m;i++)
			fscanf(in,"%d%d",l+i,r+i);
		fscanf(ans,"%d",c1+1);
		fscanf(out,"%d",c2+1);
		if((c1[1]==-1)!=(c2[1]==-1))
		{
			fprintf(stderr,"WA%d\n",i);
			continue;
		}
		for(int i=2;i<=m;i++)
			fscanf(out,"%d",c2[i]);
		init();
		if(solve())
			fprintf(stderr,"AC%d\n",i);
		else
			fprintf(stderr,"WA%d\n",i);
	}
	return 0;
}