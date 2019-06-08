#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
int s[100009];
int main()
{
	freopen("decode.in","r",stdin);
	freopen("decode.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n*n;i++)
		scanf("%d",s+i);
	printf("%dx%dt0:",n,n);
	int lst=1;
	for(int i=1;i<=n*n;i++)
	{
		if(s[i]!=-1)
		{
			if(lst<i)
				printf("%c",i-lst+'a'-1);
			lst=i+1;
			printf("%d",s[i]);
		}
	}
	if(lst<=n*n)
		printf("%c",n*n+1-lst+'a'-1);
	return 0;
}