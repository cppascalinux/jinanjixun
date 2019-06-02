#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

struct qwq{
	int a,b,c;
	double s;
};
qwq delta[1000010];

void add_delta(int i,int j,int k)
{
	delta[++ cnt].a = i;
	delta[cnt].b = j;
	dalta[cnt].c = k;
	
}

int main()
{
	freopen("three.in","r",stdin);
	freopen("three.out","w".stdout);
	
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++)
		scanf("%1d",&line[i]);
	for(int i = 1;i <= n;i ++)
		if(line[i])
		{
			flag = 1;
			break;
		}
	if(! flag) printf("0");
	else
	{
		for(int i = 1;i <= n;i ++)
			for(int j = i + 1;j <= n;j ++)
				for(int k = j + 1;k <= n;k ++)
					if(line[i] + line[j] + line[k]) add_delta(i,j,k);
	}
	
	fclose(stdin);
	fclose(stdout);
	return ~~ (0 - 0);
}
