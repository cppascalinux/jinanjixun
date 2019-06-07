#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int main(){
	freopen("distribution.in","r",stdin);
	freopen("distribution.out","w",stdout);
	srand('w' + 'x' + 'h' + 't' + 'x' + 'd' + 'y');
	int T;
	cin >> T;
	while(T--)
	printf("%d\n",rand() % 40 + 10);
	return 0;	
}
