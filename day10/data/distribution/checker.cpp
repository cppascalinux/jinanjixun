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

int m=30;

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
//	freopen("/tmp/_eval.score", "w", stderr);
	registerLemonChecker(argc, argv);
	vector<int> juryAns = read(ans); 
	vector<int> patAns = read(ouf);
	for (int i=0;i<m;i++) wr+=abs(juryAns[i]-patAns[i]);
	if (wr<=5) quitp(10.0,"wrong %d ",wr);
	else if (wr<=15) quitp(9.,"wrong %d ",wr);
	else if (wr<=150) quitp(7.,"wrong %d ",wr);
	else if (wr<=300) quitp(5.,"wrong %d ",wr);
	else if (wr<=600) quitp(3.,"wrong %d ",wr);
	else quitp(0.0,"wrong %d ",wr);
}
