#include<bits/stdc++.h>
#include"testlib.h"
#define maxn 201000
using namespace std;
int n,m;
string is[1100],ls[1100];
int os[1100][1100],vs[1100][1100];
void dfs(int x,int y){
	if(x<1||y<1||x>n||y>m)return ;
	if(vs[x][y]||ls[x][y-1]=='0')return ;
	vs[x][y]=1;
	dfs(x+1,y),dfs(x,y+1);
	dfs(x-1,y),dfs(x,y-1);
}
int main(int argc, char ** argv){
	registerLemonChecker(argc, argv);
	n=inf.readInt(1,500);
	m=inf.readInt(1,500);
	inf.readEoln();
	for(int i=1;i<=n;++i){
		is[i]=inf.readWord();
	//	for(auto c:is[i])fprintf(stderr,"[%d]",(int)c);
		if(is[i].length()!=m)quitf(_wa,"Data invalid.");
		for(auto c:is[i])if(c!='0'&&c!='1')quitf(_wa,"Data invalid.");
	}
	int x=ouf.readInt();
	int y=ans.readInt();
	if(x!=y){
		quitf(_wa,"Wrong Answer![ans=%d,yours=%d]",y,x);
		return 0;
	}
	fprintf(stderr,"[ans:%d]\n",x);
	ouf.readEoln();
	for(int T=1;T<=x;++T){
		string s=ouf.readWord();
		for(int i=1;i<=n;++i){
			ls[i]=ouf.readWord();	
			if(ls[i].length()!=m)quitf(_wa,"Solution invalid.[1]");
			for(auto c:ls[i])if(c!='0'&&c!='1')quitf(_wa,"Solution invalid.[1]");
		}
		int cnt=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				vs[i][j]=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)if(ls[i][j-1]=='1'&&!vs[i][j]){
				dfs(i,j);
				cnt++;
			}
		if(cnt!=1){
			quitf(_wa,"Solution invalid.[2]");
		}
		if(s=="+"){	
			for(int i=1;i<=n;++i)
				for(int j=1;j<=m;++j)
					os[i][j]+=ls[i][j-1]-'0';
		} else if(s=="-"){
			for(int i=1;i<=n;++i)
				for(int j=1;j<=m;++j)
					os[i][j]-=ls[i][j-1]-'0';
		} else {
			quitf(_wa,"Solution Invalid.[3]");
		}
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(os[i][j]!=(int)is[i][j-1]-'0')
				quitf(_wa,"Solution Invalid.[4]");
	quit(_ok,"Accepted!");
}
