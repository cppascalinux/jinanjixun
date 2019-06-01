#include<bits/stdc++.h>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define fgx cerr<<"-------------"<<endl
#define oyjasonhandsome_N 1000000
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
void dbg(){cerr<<endl;}
template<typename A,typename... B>void dbg(A x,B... y){cerr<<x<<" ";dbg(y...);}
#define debug(...) cerr<<#__VA_ARGS__<<"=",dbg(__VA_ARGS__)
vector<int> oyjasonhandsome_cur; int oyjasonhandsome_sz;
struct oyjasonhandsome_node{int oyjasonhandsome_l,oyjasonhandsome_r;vector<int> oyjasonhandsome_v;}
oyjasonhandsome_a[oyjasonhandsome_N];
void oyjasonhandsome_build(int oyjasonhandsome_l,int oyjasonhandsome_r,int oyjasonhandsome_o)
{	oyjasonhandsome_a[oyjasonhandsome_o].oyjasonhandsome_l=oyjasonhandsome_l;
	oyjasonhandsome_a[oyjasonhandsome_o].oyjasonhandsome_r=oyjasonhandsome_r;
	if(oyjasonhandsome_l==oyjasonhandsome_r) return;
	int oyjasonhandsome_mid=(oyjasonhandsome_l+oyjasonhandsome_r)>>1;
	oyjasonhandsome_build(oyjasonhandsome_l,oyjasonhandsome_mid,oyjasonhandsome_o+oyjasonhandsome_o);
	oyjasonhandsome_build(oyjasonhandsome_mid+1,oyjasonhandsome_r,oyjasonhandsome_o+oyjasonhandsome_o+1);
}
void oyjasonhandsome_add(int oyjasonhandsome_l,int oyjasonhandsome_r,int oyjasonhandsome_x,int oyjasonhandsome_o)
{	if(oyjasonhandsome_a[oyjasonhandsome_o].oyjasonhandsome_l==oyjasonhandsome_l&&oyjasonhandsome_a[oyjasonhandsome_o].oyjasonhandsome_r==oyjasonhandsome_r)
	{oyjasonhandsome_a[oyjasonhandsome_o].oyjasonhandsome_v.push_back(oyjasonhandsome_x);return;}
	int oyjasonhandsome_mid=(oyjasonhandsome_a[oyjasonhandsome_o].oyjasonhandsome_l+oyjasonhandsome_a[oyjasonhandsome_o].oyjasonhandsome_r)>>1;
	if(oyjasonhandsome_r<=oyjasonhandsome_mid) oyjasonhandsome_add(oyjasonhandsome_l,oyjasonhandsome_r,oyjasonhandsome_x,oyjasonhandsome_o+oyjasonhandsome_o);
	else if(oyjasonhandsome_l>oyjasonhandsome_mid) oyjasonhandsome_add(oyjasonhandsome_l,oyjasonhandsome_r,oyjasonhandsome_x,oyjasonhandsome_o+oyjasonhandsome_o+1);
	else oyjasonhandsome_add(oyjasonhandsome_l,oyjasonhandsome_mid,oyjasonhandsome_x,oyjasonhandsome_o+oyjasonhandsome_o),oyjasonhandsome_add(oyjasonhandsome_mid+1,oyjasonhandsome_r,oyjasonhandsome_x,oyjasonhandsome_o+oyjasonhandsome_o+1);
}
void oyjasonhandsome_ins(int oyjasonhandsome_x)
{	for(rint oyjasonhandsome_i=29;oyjasonhandsome_i>=0;oyjasonhandsome_i--)
	if(oyjasonhandsome_x>>oyjasonhandsome_i&1)
	{	if(!oyjasonhandsome_cur[oyjasonhandsome_i])
		{oyjasonhandsome_cur[oyjasonhandsome_i]=oyjasonhandsome_x;++oyjasonhandsome_sz;return;}
		oyjasonhandsome_x^=oyjasonhandsome_cur[oyjasonhandsome_i];
	}
}
void oyjasonhandsome_gao(int oyjasonhandsome_o)
{	for(rint oyjasonhandsome_i=0;oyjasonhandsome_i<oyjasonhandsome_a[oyjasonhandsome_o].oyjasonhandsome_v.size();oyjasonhandsome_i++)
	oyjasonhandsome_ins(oyjasonhandsome_a[oyjasonhandsome_o].oyjasonhandsome_v[oyjasonhandsome_i]);
	vector<int> oyjasonhandsome_is_true=oyjasonhandsome_cur; int oyjasonhandsome_la=oyjasonhandsome_sz;
	if(oyjasonhandsome_a[oyjasonhandsome_o].oyjasonhandsome_l==oyjasonhandsome_a[oyjasonhandsome_o].oyjasonhandsome_r)
	{cout<<(1<<oyjasonhandsome_sz)<<"\n";return;}
	oyjasonhandsome_gao(oyjasonhandsome_o+oyjasonhandsome_o);
	oyjasonhandsome_cur=oyjasonhandsome_is_true,oyjasonhandsome_sz=oyjasonhandsome_la;
	oyjasonhandsome_gao(oyjasonhandsome_o+oyjasonhandsome_o+1);
}
map<int,int> oyjasonhandsome_la;
int main()
{	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	int oyjasonhandsome,oyjasonhandsome_q,oyjasonhandsome_tp,oyjasonhandsome_x; cin>>oyjasonhandsome>>oyjasonhandsome_q;
	oyjasonhandsome_cur.resize(30); oyjasonhandsome_build(1,oyjasonhandsome_q,1);
	for(rint oyjasonhandsome_i=1;oyjasonhandsome_i<=oyjasonhandsome_q;oyjasonhandsome_i++)
	{	scanf("%d%d",&oyjasonhandsome_tp,&oyjasonhandsome_x);
		if(oyjasonhandsome_tp==1) oyjasonhandsome_la[oyjasonhandsome_x]=oyjasonhandsome_i;
		else oyjasonhandsome_add(oyjasonhandsome_la[oyjasonhandsome_x],oyjasonhandsome_i-1,oyjasonhandsome_x,1),oyjasonhandsome_la[oyjasonhandsome_x]=0;
	}
	for(map<int,int>::iterator oyjasonhandsome_it=oyjasonhandsome_la.begin();oyjasonhandsome_it!=oyjasonhandsome_la.end();oyjasonhandsome_it++)
	if(oyjasonhandsome_it->second) oyjasonhandsome_add(oyjasonhandsome_it->second,oyjasonhandsome_q,oyjasonhandsome_it->first,1);
	oyjasonhandsome_gao(1);
	return 0;
}

