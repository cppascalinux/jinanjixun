#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#include<ctime>
#include<set>
using namespace std;
int main()
{
	freopen("xor.in","w",stdout);
	mt19937 rnd(time(0));
	int m=30,q=100000;
	printf("%d %d\n",m,q);
	set<int> s;
	for(int i=1;i<=q;i++)
	{
		int tp=rnd()%2;
		if(tp||s.empty())
		{
			int v=rnd()%(1<<m);
			s.insert(v);
			printf("1 %d\n",v);
		}
		else
		{
			while(1)
			{
				int v=rnd()%(1<<m);
				set<int>::iterator it=s.lower_bound(v);
				if(it!=s.end())
				{
					printf("2 %d\n",*it);
					s.erase(it);
					break;
				}
			}
		}
	}
	return 0;
}