#include<iostream>
#include<cstdio>
#include<cmath>
#include<set>
using namespace std;
const int N=102019;
int n,m,a[N];
set <int> s[N];bool vis[N];
set<int>::iterator it1,it2;
void getans(){
	int mi=0,opt,x,y;
	for(int i=0;i<=100000;i++)s[i].insert(1e9);
	while(m--){
		cin>>opt>>x>>y;
		x^=mi; y^=mi;
		if(opt==1){
			if(!vis[x] || x==y)continue;
			if(s[x].size()>s[y].size())swap(s[x],s[y]);
			for(it1=s[x].begin();it1!=s[x].end();++it1)
				s[y].insert(*it1);
			s[x].clear(); vis[x]=0; vis[y]=1;
		}
		else{
			if(!vis[x] || !vis[y]){
				puts("Chtholly"); mi=0; continue;
			}
			int fx=-1,fy=-1;mi=1e9;
			it1=s[x].begin(),it2=s[y].begin();
			while(*it1!=1e9 && *it2!=1e9){
				int val1=*it1,val2=*it2;
				mi=min(mi,abs(val1-val2));
				if(*(++it1)>*(++it2))--it1;
				else --it2;
			}printf("%d\n",mi);
		}
	}
}
int main()
{
	freopen("busy.in","r",stdin);
	freopen("busy.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i],s[a[i]].insert(i);vis[a[i]]=1;
	}getans();
	fclose(stdin); fclose(stdout);
	return 0;
}
