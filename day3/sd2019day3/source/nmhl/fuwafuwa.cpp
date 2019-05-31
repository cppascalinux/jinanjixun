#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

class Subtask_1 {
private:
  static const int maxn = 100000 + 10;
  int node_num;

  struct Node {
    int key, dis;
    Node *lchild, *rchild;
    Node() { key = dis = 0, lchild = rchild = NULL; }
    ~Node() {};
  };

  Node *p_root, node[maxn];

public:
  inline Node* Insert(Node *x, Node *y) {
    if( x == NULL ) return y;
    ++y->dis;
    if( x->key > y->key ) x->lchild = Insert(x->lchild, y);
    else x->rchild = Insert(x->rchild, y);
    return x;
  }

  inline void Main(int a, int b, int m, int n) {
    p_root = NULL, node_num = 0;
    for(int i = 1; i <= n; ++i) node[i] = node[maxn - 1];
    for(int i = 1; i <= n; ++i) node[++node_num].key = (a + 1ll * i * b) % m, p_root = Insert(p_root, &node[node_num]);
    printf("%d\n", node[n].dis);
  }
} subtask_1;

class Subtask_2 {
private:
  static const int maxn = 2000000 + 10;
  int div[maxn], vis[maxn], node_num;

  struct Node {
    int key, dis;
    Node *lchild, *rchild;
    Node() { key = dis = 0, lchild = rchild = NULL; }
    ~Node() {};
  };

  Node *p_root, node[maxn];

public:
  inline Node* Insert(Node *x, Node *y) {
    if( x == NULL ) return y;
    ++y->dis;
    if( x->key > y->key ) x->lchild = Insert(x->lchild, y);
    else x->rchild = Insert(x->rchild, y);
    return x;
  }

  inline void Main(int a, int b, int m, int n) {
    memset(vis, -1, sizeof vis), p_root = NULL, node_num = 0;
    for(int i = 1; i <= (m << 1); ++i) node[i] = node[maxn - 1];
    for(int i = 1; i <= n; ++i) {
      node[++node_num].key = (a + 1ll * i * b) % m, p_root = Insert(p_root, &node[node_num]);
      if( vis[node[node_num].key] == -1 ) vis[node[node_num].key] = node[node_num].dis;
      else if( div[node[node_num].key] == 0 ) div[node[node_num].key] = node[node_num].dis - vis[node[node_num].key];
      else break;
    }
    int ans = vis[(a + 1ll * n * b) % m] + div[(a + 1ll * n * b) % m] * ((a + 1ll * n * b) / m - 1);
    printf("%d\n", ans);
  }
} subtask_2;

int a, b, m, n;

int main(int argc, char const *argv[])
{
  freopen("fuwafuwa.in", "r", stdin), freopen("fuwafuwa.out", "w", stdout);

  scanf("%d", &n);
  while( ~scanf("%d%d%d%d", &a, &b, &m, &n) ) m <= 1000000 ? subtask_2.Main(a, b, m, n) : subtask_1.Main(a, b, m, n);

  return 0;
}