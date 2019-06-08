
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M 10001000
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
int k, q, up;
int note[M], v[M];

bool cmp(int a, int b)
{
	int x = a, y = b;
	while(x < up && y < up)
	{
		if(v[x] != v[y]) return v[x] < v[y];
		x++, y++;
	}
	return x > y;
}

int main() {
	freopen("string.in", "r", stdin); freopen("string.out", "w", stdout);
	k = read(), q = read();
	up = (1 << k);
	for(int i = 0; i < up; i++) {
		v[i] = v[i >> 1] ^ (i & 1);
	}
	for(int i = 1; i <= up; i++) note[i] = i - 1;
	sort(note + 1, note + up + 1, cmp);
	
	while(q--) {
		cout << note[read()] << " ";
	}
	return 0;
}


