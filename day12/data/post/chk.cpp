#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
typedef long long ll;

const int N=200100;

int n,k;
ll a[N],shop[N],l;

ll readAns(InStream& stream) {
	ll ans=stream.readLong();
	for (int i=0;i<k;i++) shop[i]=stream.readLong(0,l-1);
	for (int i=1;i<k;i++) {
		if (shop[i-1]>shop[i]) quitf(_wa, "the coordinates of shops should be non-decreasing ");
	}
	ll pans=0;
	for (int i=0;i<n;i++) {
		int c=lower_bound(shop,shop+k,a[i])-shop;
		if (c==k) c=0;
		ll cur=min(abs(a[i]-shop[c]),l-abs(a[i]-shop[c]));
		if (c==0) c=k-1; else --c;
		cur=min(cur,min(abs(a[i]-shop[c]),l-abs(a[i]-shop[c])));
		pans+=cur;
	}
	if (pans!=ans) quitf(_wa, "your solution doesn't match your answer ");
	return pans;	
}

int main(int argc,char *argv[]) {
	registerLemonChecker(argc, argv);
	n=inf.readInt();
	k=inf.readInt();
	l=inf.readLong();
	for (int i=0;i<n;i++) a[i]=inf.readLong();
	ll jans=ans.readLong();
	ll pans=readAns(ouf);
    if (jans < pans)
        quitf(_wa, "jury has the better answer: jans = %lld, pans = %lld\n", jans, pans);
    else if (jans == pans)
        quitf(_ok, "answer = %lld\n", pans);
    else // (jans > pans)
        quitf(_fail, ":( participant has the better answer: jans = %lld, pans = %lld\n", jans, pans);
}
