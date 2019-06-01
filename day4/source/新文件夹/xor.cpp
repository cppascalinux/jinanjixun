#include<bits/stdc++.h>
#define to first
#define da second
using namespace std;
int m,q,cz,x,sz[1030],lsz;
pair<int,int> bc[1030];
int getf(int f){
	if(bc[f].to==f){
		return f;
	}
	return (bc[f].to=getf(bc[f].to));
}
int hbi(int a,int b){
	int aa=getf(a),bb=getf(b);
	if(aa!=bb){
		int yx=bc[aa].da;
		bc[aa].to=bb;
		bc[bb].da+=yx;
		return bc[bb].da;
	}
	return 0;
}

void zdlt(){
	int ans=1;
	memset(bc,0,sizeof(bc));
	for(int i=0;i<1030;i++){
		bc[i].da=1;
		bc[i].to=i;
	}
	for(int i=0;i<lsz;i++){
		for(int ii=0;ii<1024;ii++){
			ans=max(hbi(sz[i]^ii,ii),ans);
		}
	}
	printf("%i\n",ans);
}
int main(){
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);

	scanf("%i%i",&m,&q);
	for(int i=0;i<q;i++){
		scanf("%i%i",&cz,&x);
		if(cz==1){
			sz[lsz]=x;
			lsz++;
			zdlt();
		}else{
			for(int ii=0;ii<lsz;ii++){
				if(sz[ii]==x){
					sz[ii]=sz[lsz];
					lsz--;
					break;
				}
			}
			zdlt();
		}
	}
	return 0;
}


