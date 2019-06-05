#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <queue>
const int RP = (1 << 27) - 1;
inline int flip(int x) {
  int ans = 0;
  for(int i = 0; i < 27; i ++) {
    if((1 << (27 - i - 1)) & x) ans |= (1 << i);
  }
  return ans;
}

namespace ST {
  struct Node {
    Node *lc, *rc;
    int cntv, xorv, tagv;
    void maintain();
    void paint(int);
    void pushdown();
  };
  Node *nil, *cnt; Node pool[3000005];
  std::vector<Node*> d_pool;
  void init_pool() {
    nil = cnt = pool;
    nil -> lc = nil -> rc = nil;
    nil -> cntv = nil -> xorv = nil -> tagv = 0;
  }
  Node *alloc_node() {
    Node *ret;
    if(!d_pool.empty()) {
      ret = d_pool.back(); d_pool.pop_back();
    } else {
      ret = ++ cnt;
    }
    ret -> lc = ret -> rc = nil;
    ret -> cntv = 1; ret -> tagv = 0;
    return ret;
  }
  
  void Node::maintain() {
    cntv = lc -> cntv + rc -> cntv;
    int xv = (lc -> xorv ^ rc -> xorv) << 1;
    if(1 & (rc -> cntv)) xv |= 1;
    xorv = xv;
  }
  void Node::paint(int x) {
    if(!cntv) return;
    tagv ^= x;
    if(1 & cntv) xorv ^= x;
    if(1 & x) std::swap(lc, rc);
  }
  void Node::pushdown() {
    if(tagv) {
      lc -> paint(tagv >> 1);
      rc -> paint(tagv >> 1);
      tagv = 0;
    }
  }
  void del_node(Node *o) {
    d_pool.push_back(o);
  }
  
  Node *gen_chain(int L, int R, int p) {
    Node *ret = alloc_node();
    if(L < R) {
      int M = (L + R) / 2;
      if(p <= M) ret -> lc = gen_chain(L, M, p);
      else ret -> rc = gen_chain(M + 1, R, p);
      ret -> maintain();
    }
    return ret;
  }
  inline bool is_leaf(Node *o) {
    return (o -> lc == nil && o -> rc == nil);
  }
  Node *merge(Node *l, Node *r) {
    if(l == nil) return r;
    if(r == nil) return l;
    l -> pushdown(); r -> pushdown();
    l -> cntv += r -> cntv;
    l -> xorv ^= r -> xorv;
    l -> lc = merge(l -> lc, r -> lc);
    l -> rc = merge(l -> rc, r -> rc);
    del_node(r);
    return l;
  }
  Node *split(Node *o, int L, int R, int s) {
    Node *p = alloc_node();
    if(L == R) {
      p -> cntv = o -> cntv - s;
      o -> cntv = s;
    } else {
      o -> pushdown();
      int M = (L + R) / 2;
      if(o -> lc -> cntv > s) {
        p -> lc = split(o -> lc, L, M, s);
      } else {
        p -> lc = o -> lc;
        o -> lc = nil;
        if(o -> lc -> cntv < s) {
          p -> rc = split(o -> rc, M + 1, R, s - o -> lc -> cntv);
        }
      }
      o -> maintain();
      p -> maintain();
    }
    return p;
  }
};

namespace AT {
  using pii = std::pair<int, int>;
  const double alpha = 0.66666;
  struct Node {
    Node *ch[2];
    int s; pii key; ST::Node* val;
    int del_s, del_cnt, tagv;
    int cmp(pii x) {
      if (x == key) {
        return -1;
      } else {
        if (x < key) {
          return 0;
        } else {
          return 1;
        }
      }
    }
    void maintain() {
      s = 1 + ch[0] -> s + ch[1] -> s;
      del_s = del_cnt + ch[0] -> del_s + ch[1] -> del_s;
    }
    int rs() { return s - del_s; }
    int rcnt() { return 1 - del_cnt; }
    void paint(int);
    void pushdown();
  };
  const int maxno = 100005;
  Node pool[maxno];
  Node *sta[maxno];
  Node *nil;
  Node *tot;
  int stot;
  void init_pool() {
    tot = nil = pool;
    stot = 0;
    nil -> ch[0] = nil -> ch[1] = nil;
    nil -> s = nil -> del_s = nil -> del_cnt = 0;
  }
  Node *alloc_node(pii x, ST::Node *nd = ST::nil, int cnt = 1) {
    Node *ret;
    if (stot > 0) {
      ret = sta[-- stot];
    } else {
      ret = ++ tot;
    }
    ret -> key = x; ret -> val = nd;
    ret -> ch[0] = ret -> ch[1] = nil;
    ret -> s = cnt;
    ret -> del_s = ret -> del_cnt = 0;
    return ret;
  }
  void del_node(Node *x) { sta[stot++] = x; }

  Node *build_tree(int *A, ST::Node **B, int L, int R) {
    if (L > R)
      return nil;
    int M = (L + R) / 2;
    Node *ret = alloc_node(A[M], B[M]);
    ret -> ch[0] = build_tree(A, B, L, M - 1);
    ret -> ch[1] = build_tree(A, B, M + 1, R);
    ret -> maintain();
    return ret;
  }
  void expand(Node *x, int *A, ST::Node **B, int &cnt) {
    if(x -> ch[0] != nil) {
      expand(x -> ch[0], A, B, cnt);
    }
    if(1 > x -> del_cnt) {
      A[++ cnt] = x -> key;
      B[cnt] = x -> val;
    }
    if (x->ch[1] != nil) {
      expand(x -> ch[1], A, B, cnt);
    }
    del_node(x);
  }
  Node *refact(Node *x) {
    static int A[maxno];
    static ST::Node *B[maxno];
    int cnt = 0;
    expand(x, A, B, cnt);
    Node *ret = build_tree(A, B, 1, cnt);
    return ret;
  }
  Node *rt;
  Node *check(Node *x, pii v) {
    if (x == nil)
      return x;
    if ((double)std::max(x -> ch[0] -> s, x -> ch[1] -> s) > alpha * (double)(x -> s)) {
      return refact(x);
    } else {
      int d = x -> cmp(v);
      if (d == 0) {
        x -> ch[0] = check(x -> ch[0], v);
      }
      if (d == 1) {
        x -> ch[1] = check(x -> ch[1], v);
      }
      x -> maintain();
      return x;
    }
  }
  void insert(Node *&x, pii v, ST::Node *val) {
    if (x == nil) {
      x = alloc_node(v, val);
      return;
    }
    int d = x -> cmp(v);
    if (d == -1) {
      assert(x -> del_cnt);
      x -> del_cnt = 0;
      x -> val = val;
    } else {
      insert(x -> ch[d], v);
    }
    x -> maintain();
  }
  void ins(int v, ST::Node *val) {
    insert(rt, v, val);
    rt = check(rt, v);
  }
  void erase(Node *x, pii v) {
    int d = x -> cmp(v);
    if (d == -1) {
      x -> del_cnt ++;
    } else {
      erase(x -> ch[d], v);
    }
    x -> maintain();
  }
  void del(pii v) {
    erase(rt, v);
    if (rt -> rs() <= alpha * rt -> s) {
      rt = refact(rt);
    }
  }
  
  std::pair<pii, ST::Node*> access(Node *o, int v) {
    if(o == nil) assert(false);
    
  }
};

int main() {
  
  return 0;
}
