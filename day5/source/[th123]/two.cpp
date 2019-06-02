#include <map>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

static const int maxn = 100000 + 10;
int n, k, node_num, ans; char str[maxn];

class Subtask_1 {
private:
  static const int maxx = 1000 + 10;

  struct Node {
    int len;
    std::vector<int> v;
    std::map<char, Node*> ma;
  } node[maxx * maxx], *p_root;
  
  inline void Insert(int s) {
    Node *x = p_root;
    for(int i = s; i <= n; x->v.push_back(s), ++i) {
      if( x->ma[str[i]] ) x = x->ma[str[i]];
      else x = (x->ma[str[i]] = &node[++node_num]), x->len = i - s + 1;
    }
  }

  inline void Deep_fs(Node *x) {
    int res = 1;
    for(int i = 1; i < x->v.size(); ++i) if( x->v[i] > x->v[i - 1] + x->len ) ++res;
    for(map<char, Node*>::iterator i = x->ma.begin(); i != x->ma.end(); ++i) Deep_fs(i->second);
    if( x->len ) ans = ans + (res == k);
  }

public:
  inline void Main() {
    p_root = &node[0];
    for(int i = 1; i <= n; ++i) Insert(i);
    Deep_fs(p_root), printf("%d\n", ans);
  }
} subtask_1;


int main(int argc, char const *argv[])
{
  freopen("two.in", "r", stdin), freopen("two.out", "w", stdout);

  scanf("%s", str + 1), scanf("%d", &k), n = strlen(str + 1);
  subtask_1.Main();

  return 0;
}