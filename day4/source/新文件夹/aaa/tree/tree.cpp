#include<bits/stdc++.h>
using namespace std;
struct tree{
	int d;
	int m;
	
	bool hpoint;bool wpoint;
}tr[100005];
int m,n,q,h[100005],w[100005],l=1,co;
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	for(int i=0;i<n;i++){
		int u,v;
		scanf("%i%i",&u,&v);
		if(v>u){
			u+=v;
			v=u-v;
			u=u-v;
		}
		tr[v].d=tr[u].d;
		tr[v].m=tr[u].m;
		
		
	}
	for(int i=0;i<m;i++){
		scanf("%i%i",h+i,w+i);
		if(h[i]>w[i]){
			w[i]+=h[i];
			h[i]=w[i]-h[i];
			w[i]=w[i]-h[i];
		}
	}
	for(int i=0;i<q;i++){
	int aa,bb;
	scanf("%i%i",&aa,&bb);	
		for(int ii=aa;ii<bb;ii++){
			
			tr[h[ii]].hpoint=1;
			tr[w[ii]].wpoint=1;
		}
		for(int ii=0;1;ii++){
			if(tr[i].hpoint){
				co++;
			}else
			if(tr[i].wpoint){
				co--;
			}
			if(!co){
				l++;
			}
		}
	}
	return 0;
}
