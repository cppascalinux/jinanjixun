#include<bits/stdc++.h>
#include"testlib.h"
#define maxn 201000
using namespace std;
map<int,int> st;
int n,m,li[maxn],ri[maxn],wi[maxn];
int main(int argc, char ** argv){
	registerLemonChecker(argc, argv);
	m=inf.readInt(),n=inf.readInt();
	for(int i=1;i<=m;++i){
		li[i]=inf.readInt(1,n);
		ri[i]=inf.readInt(1,n);
		wi[i]=inf.readInt(-1,1);
		if(li[i]>ri[i])quitf(_wa,"input file invalid.");
	}
	int no_sol=0,no_sol2=0;
	for(int i=1;i<=m;++i){
		int x=ouf.readInt(-1,1);
		if(x==-1&&i!=1)quitf(_wa,"invalid:print -1");
		else if(x==-1){no_sol=1;break;}
		if(wi[i]!=-1&&x!=wi[i])quitf(_wa,"You change the jode!");
		if(x==0)x=-1;
		st[li[i]]+=x,st[ri[i]+1]-=x;
	}
	if(no_sol==0){
		int sum=0;
		for(map<int,int>::iterator it=st.begin();it!=st.end();it++){
			pair<int,int> d=*it;
			sum+=d.second;
			if(abs(sum)>1)quitf(_wa,"invalid jode");
		}
	}
	int x=ans.readInt(-1,1);
	if(x==-1)no_sol2=1;
	if(no_sol^no_sol2)quitf(_wa,"WXH has found a solution");
	quit(_ok,"Accepted!");
}
