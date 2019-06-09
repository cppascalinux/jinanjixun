#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
typedef long long ll;

const int N=200100;

int w[N],n,k;

int main(int argc,char *argv[]) {
	registerLemonChecker(argc, argv);
	n=inf.readInt();
	k=inf.readInt();
	int p1=ans.readInt();
	int m=ouf.readInt();
	if ((p1==-1)!=(m==-1)) {
		quitf(_wa,"first line is wrong");
	}
	if (p1==-1) quitf(_ok,"ok");
	if (m>3*n) quitf(_wa,"too many opers");
	for (int i=1;i<=n;i++) w[i]=1;
	for (int i=0;i<m;i++) {
		int u=ouf.readInt(1,n),v=ouf.readInt(1,n);
		if (u==v || w[u]<w[v]) quitf(_wa,"invalid oper");
		w[u]-=w[v]; w[v]*=2;
	}
	if (w[1]!=k) {
		quitf(_wa,"first bottle is not k");
	}
	quitf(_ok,"ok");
}
