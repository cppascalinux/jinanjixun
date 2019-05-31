#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 1111111

int read()
{
	int ret=0,neg=1;
	char c=getchar();
	while (c<'0' || c>'9'){
		if (c=='-') neg=-1;
		c=getchar();
	}
	while (c>='0' && c<='9'){
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*neg;
}

struct Node{
	int key,deep;
	Node *lson,*rson;
};
Node pool[MAXN];
int cnt;
int t,a,b,m,n;
Node *root;

Node *newnode(int val)
{
	pool[++cnt].key=val;pool[cnt].lson=pool[cnt].rson=NULL;
	return &pool[cnt];
}

Node *ins(Node *x,Node *y,int deep)
{
	if (x==NULL){
		y->deep=deep;
		return y;
	}
	if (x->key>y->key) x->lson=ins(x->lson,y,deep+1);
	else x->rson=ins(x->rson,y,deep+1);
	return x;
}

int main()
{
	freopen("fuwafuwa.in","r",stdin);
	freopen("fuwafuwa.out","w",stdout);
	t=read();
	while (t--){
		root=NULL;cnt=0;
		a=read();b=read();m=read();n=read();
		for (int i=1;i<=n;i++){
			Node *x=newnode((1ll*i*b+a)%m);
			root=ins(root,x,0);
			if (i==n) printf("%d\n",x->deep);
		}
	}
}
