#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
const int maxn=1000001;

int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}

int n,m,a[maxn];
set<pair<int,int>>s;

void DEL(int l,int r){
	while(1&&(!s.empty())){
		pair<int,int> v=*s.lower_bound(mp(r,n));
		if (v.second<l) return;
		s.erase(v);
		if (v.first<l) s.insert(mp(v.first,l-1));
		if (v.second>r) s.insert(mp(r+1,v.second));
	}
}

void ADD(int l,int r){
	int L=l,R=r;
	while(1&&(!s.empty())){
		pair<int,int> v=*s.lower_bound(mp(r,n));
		if (v.second<l) return;
		s.erase(v);
		L=min(L,v.first);
		R=max(R,v.second);
	}
	s.insert(mp(L,R));
}

int SUM(int l,int r){
	set<pair<int,int>>::iterator pos=s.lower_bound(mp(l,n));
	int res=0;
	while(1){
		pair<int,int> v=*pos;
		if (v.first>r) break;
		if (v.second>=l)
		res+=min(r,v.second)-max(l,v.first)+1;
		pos++;
	}
}

int ORL(int l,int r){
	set<pair<int,int>>::iterator pos=s.lower_bound(mp(l,n));
	int res=0;
	while(1){
		pair<int,int> v=*pos;
		if (v.first>r) break;
		res+=min(r,v.second)-max(l,v.first)+1;
		pos++;
	}
}

int main(){
	n=read(),m=read();
	int l=0,r=0;
	for (int i=1;i<=n;++i){
		a[i]=read();
		if (a[i]&&(!l)) l=i;
		if (l&&a[i]) r=i;
		if (!a[i]&&l&&r) s.insert(mp(l,r)),l=0;
	}
	if (l) s.insert(mp(l,r));
	for (auto v:s){
		cout<<v.first<<" "<<v.second<<endl;
	}
	for (int i=1;i<=m;++i){
		
	}
}
