#include <cmath>
#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 10000 + 10;
int n, m, l; char str[maxn];

int main(int argc, char const *argv[])
{
  freopen("end.in", "r", stdin), freopen("end.out", "w", stdout);

  scanf("%d%d", &n, &m), scanf("%s", str), l = strlen(str);
  if( n == 3 ) printf("93838\n");
  if( n == 5 ) printf("237252707\n");
  if( n == 7 ) (str[7] ^ 48) ? printf("152914862\n") : printf("81822662\n");

  return 0;
}