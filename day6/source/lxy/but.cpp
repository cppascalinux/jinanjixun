#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#define il inline
#define re register
#define gc getchar
#define LL long long
using namespace std;
template <typename T>
void rd(T &s)
{
	s = 0;
	bool p = 0;
	char ch;
	while (ch = gc(), p |= ch == '-', !isdigit(ch));
	while (s = s * 10 + ch - '0', ch = gc(), isdigit(ch));
	s *= (p ? -1 : 1);
}
typedef pair<int, int> P;
P poi[1000];
int w[1000];
int main()
{
	srand(time(NULL));
#ifdef DEBUG
	cout << "This is stdin&stdout\n";
#else
	freopen("but.in", "r", stdin);
	freopen("but.out", "w", stdout);
#endif
	int n;
	rd(n);
	for (int i = 1; i <= n; ++i)
		rd(poi[i].first), rd(poi[i].second), rd(w[i]);
	sort(w + 1, w + n + 1);
	int ans = w[1] + w[2];
	for (int i = 3; i <= n; ++i)
	{
		ans += w[i];
		printf("%d ", ans <= 0 ? -1 : ans);
	}
	return 0;
}
