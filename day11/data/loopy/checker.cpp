#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <deque>
#include <list>
#include <bitset>
#include <sstream>
#include "testlib.h"

using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)

const int N=35;
int n,cnum,sat,m,per[N][N],vis[N][N],edge[N][N];
int x[N*N],y[N*N];

int score,wr;
vector<int> read(InStream &in) {
	vector<int> d;
	for (int i=0;i<m;i++) {
		int x=in.readInt(1,100,"n");
		d.push_back(x);
	}
	return d;
}

void print_score() {
	fprintf(stderr, "%d\n", score/2);
}



int main(int argc, char **argv) {
	registerLemonChecker(argc, argv);
	n=inf.readInt();
	cnum=0;
	rep(i,1,n+1) rep(j,1,n+1) {
		per[i][j]=inf.readInt();
		if (per[i][j]!=-1) cnum++;
	}

	m=ouf.readInt();
	rep(i,0,m) {
		x[i]=ouf.readInt();
		y[i]=ouf.readInt();
		if (x[i]<0||x[i]>n||y[i]<0||y[i]>n||vis[x[i]][y[i]]) {
			quitf(_wa,"not a cycle");
		}
		vis[x[i]][y[i]]=1;
	}
	rep(i,0,m) {
		int dis=abs(x[i]-x[(i+1)%m])+abs(y[i]-y[(i+1)%m]);
		if (dis!=1) {
			quitf(_wa,"not a cycle");
		}
	}
	rep(i,0,m) {
		int px=x[i],py=y[i],qx=x[(i+1)%m],qy=y[(i+1)%m];
		if (px==qx) {
			if (py>qy) swap(py,qy);
			edge[px+1][py+1]++;
			edge[px][py+1]++;
		} else {
			if (px>qx) swap(px,qx);
			edge[px+1][py+1]++;
			edge[px+1][py]++;
		}
	}
	sat=0;
	rep(i,1,n+1) rep(j,1,n+1) if (per[i][j]==edge[i][j]) sat++;
	if (cnum==sat) quitp(10.0, "ok %d/%d", cnum,sat);
	else if (cnum*19<=sat*20) quitp(7.0, "ok %d/%d", cnum,sat);
	else if (cnum*16<=sat*20) quitp(5.0, "ok %d/%d", cnum,sat);
	else if (cnum*14<=sat*20) quitp(4.0, "ok %d/%d", cnum,sat);
	else if (cnum*12<=sat*20) quitp(3.0, "ok %d/%d", cnum,sat);
	else if (cnum*8<=sat*20) quitp(2.0, "ok %d/%d", cnum,sat);
	else if (cnum*4<=sat*20) quitp(1.0, "ok %d/%d", cnum,sat);
	else quitp(0.0, "ok %d/%d", cnum,sat);
}
