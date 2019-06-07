#include<bits/stdc++.h>
#define swkakioi 1
#define ll long long
#define R register
using namespace std;
template <class swkaknoi> inline void read(swkaknoi &x)
{
	x=0;
	char ch=getchar(), w=0;
	while(!isdigit(ch))w=(ch=='-'), ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=w?-x:x;
}
int T;
int main()
{
	freopen("distribution.in", "r", stdin);
	freopen("distribution.out", "w", stdout);
	srand(time(0));
	read(T);
	while(T--)
		cout<<rand()%100+1<<endl;
	return 0;
}
