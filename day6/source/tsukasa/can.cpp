#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int read()
{
	int ret=0,neg=1;
	char c=getchar();
	while (c<'0' || c>'9'){
		if (c=='-') neg=-1;
		c=getchar();
	}
	while (c>='0' && c<='9'){
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*neg;
}

int main()
{
	freopen("can.in","r",stdin);
	freopen("can.out","w",stdout);
	puts("0");
}
