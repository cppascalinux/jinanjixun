#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+1;

int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}

int n,m,top;
vector<int>pos[maxn];

int id[maxn];

void Rough(){
	int lastans=0;
	for (register int k=1;k<=m;++k){
		int op=read(),x=read(),y=read();
		x^=lastans,y^=lastans;
		if (op==1){
			if (!pos[id[x]].size()||x==y) continue;
			int tag=id[y]?id[y]:id[y]=++top;
			int cur=id[x];
			for (register auto v:pos[cur])
			pos[tag].push_back(v);
			sort(pos[tag].begin(),pos[tag].end());
			pos[cur].clear();id[x]=0;
		}
		if (op==2){
			if ((!id[x])||(!id[y])){
				lastans=0;puts("Chtholly");continue;
			}
			x=id[x],y=id[y];
			int cur=0,res=n;
			for (register auto v:pos[x]){
				while(pos[y][cur+1]<=v&&cur+1<pos[y].size()) cur++;
				res=min(res,abs(v-pos[y][cur]));
				if (cur+1<pos[y].size())
				res=min(res,abs(v-pos[y][cur+1]));
			}
			printf("%d\n",lastans=res);
		}
	}
}

int main(){
	freopen("busy.in","r",stdin);
	freopen("busy.out","w",stdout);
	n=read(),m=read();
	for (register int i=1;i<=n;++i){
		int x=read();
		if (!id[x]) id[x]=++top;
		pos[id[x]].push_back(i);
	}
	Rough();
}
