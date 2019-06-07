#include <bits/stdc++.h>
using namespace std;

void build(int n){
	for (int i=2;i<=n;++i)
	cout<<rand()%(i-1)+1<<" "<<i<<" "<<rand()%100000+1<<endl;
}

int main(){
	srand((int)time(0));
	freopen("tree.in","w",stdout);
	int n=3000;
	cout<<n<<endl;
	build(n);build(n);
}
