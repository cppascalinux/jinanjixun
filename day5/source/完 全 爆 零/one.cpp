#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
int a[23];
int main()
{
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	if(a[1]>a[2]) putchar('1');
	else putchar('0');
	fclose(stdin);
	fclose(stdout);
	return 0;
}
