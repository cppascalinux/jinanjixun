#include<bits/stdc++.h>
#include"testlib.h"
#define maxn 201000
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
int a[2010][2010],vs[2010][2010],vscol[2010],b[2010][2010];
ll s[2010],c[2010];
int main(int argc, char ** argv){
	int sss=-1;
	if(argc<2){
		printf("Program must be run with the following arguments: <case-id>\n");
		return 0;
	}
	sscanf(argv[1],"%d",&sss);
//	printf("[%s]",argv[1]);
	char* _argv[4];
	for(int i=0;i<4;++i)
		_argv[i]=new char[100];
	sprintf(_argv[0],"%s",argv[0]);
	sprintf(_argv[1],"cut%d.in",sss);
	sprintf(_argv[2],"cut%d.out",sss);
	sprintf(_argv[3],"cut%d.ans",sss);
	registerTestlibCmd(4, _argv);
	int n=inf.readInt(),m=inf.readInt(),K=inf.readInt(),W=inf.readInt(1,1e9);
//	printf("[%d,%d(%s)]",n,m,arg);
	for(int i=1;i<=n;++i) 
		for(int j=1;j<=m;++j)
			a[i][j]=inf.readInt(1,W);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			b[i][j]=ouf.readInt(1,K);
			s[b[i][j]]+=a[i][j];
		}
	for(int i=1;i<=10;++i)
		c[i]=ans.readLong();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)if(!vs[i][j]){
			if(vscol[b[i][j]]){
				quitf(_wa,"col[%d] Disconnected.\n",b[i][j]);
				return 0;
			}
			vscol[b[i][j]]=1;
			queue<pii> Q;
			Q.push(pii(i,j));
			while(Q.size()){
				pii p=Q.front();
				Q.pop();
				vs[p.first][p.second]=1;
				for(int k=0;k<4;++k){
					int x=p.first+dx[k];
					int y=p.second+dy[k];
					if(x<=0||y<=0||x>n||y>m)continue;
					if(vs[x][y]||b[x][y]!=b[i][j])continue;
					vs[x][y]=1;
					Q.push(pii(x,y));
				}
			}
		}
	for(int i=1;i<=K;++i)if(!vscol[i]){
		quitf(_wa,"col[%d] not appear.\n",i);
		return 0;
	}
	ll mx=*max_element(s+1,s+K+1);
	ll mn=*min_element(s+1,s+K+1);
	int ans=0;
	for(int i=1;i<=10;++i)ans+=c[i]>=mx-mn;
	if(ans==10){
		char msg[100];
		sprintf(msg,"Accepted! your Answer is [max-min=%lld].\n",mx-mn);
		quit(_ok,msg);
	} else {
		char msg[100];
		sprintf(msg,"your Answer is [max-min=%lld].\n",mx-mn);
		quitp((long double)ans/10.0,msg);
	}
}
