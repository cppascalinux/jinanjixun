#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define maxn 1000001
#define re register
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
using namespace std;

int n, m, c, r, t, x, y, z, sq, anss, bl[maxn];
int a[maxn], b[maxn], ans[maxn], cnt[maxn], lef[maxn], rig[maxn], chg[maxn], num[maxn];
int chbl[maxn], chrig[maxn][2], chlef[maxn][2], chcnt[maxn][2], chnum[maxn][2];
int ifbl[maxn];

struct hz {  
    int l;
    int r;
    int id;
    inline bool operator <(const hz &o)const {
        return (b[l] == b[o.l])? r < o.r : l < o.l;
    }  
}h[maxn];

//chrig[++chrig[0][0]][0] = rig[a[x]-1]; chrig[chrig[0][0]][1] =  rig[lef[a[x]-1]];
//			chlef[++chlef[0]] = lef[]

int query(int x, int y) { //左右相同的 
    int res = 0;
    FOR(i, x, y) {
    	if(bl[a[x]])
    	  continue;
    	bl[a[x]] = 1;
    	chbl[++chbl[0]] = a[x];
    	if(bl[a[x]-1] == 1 && bl[a[x]+1] == 1) {
    		rig[lef[a[x]-1]] = rig[rig[a[x]+1]];
    		lef[rig[a[x]+1]] = lef[rig[a[x]-1]];
    		
    		chbl[++chbl[0]] = lef[a[x]-1];
    		chbl[++chbl[0]] = rig[a[x]+1];
    		
    		chbl[++chbl[0]] = num[lef[a[x]-1]];
    		chbl[++chbl[0]] = num[lef[a[x]-1]];
    		
    		--cnt[num[lef[a[x]-1]]]; --cnt[num[rig[a[x]+1]]];
    		num[lef[a[x]-1]] = num[rig[a[x]+1]] = num[lef[a[x]-1]] + num[rig[a[x]+1]] + 1;
    		++cnt[num[lef[a[x]-1]]]; //修改后的 

    		chbl[++chbl[0]] = num[lef[a[x]-1]];
    		continue;
		}
		if(bl[a[x]-1] == 1) {
			chbl[++chbl[0]] = num[lef[a[x]-1]];
			chbl[++chbl[0]] = num[lef[a[x]-1]+1];
			
			--cnt[num[lef[a[x]-1]]];
			++cnt[num[lef[a[x]-1]]+1];
			
			chbl[++chbl[0]] = lef[a[x]-1];
			chbl[++chbl[0]] = a[x];
			
			rig[lef[a[x]-1]] = x;
			lef[a[x]] = lef[a[x]-1];
			num[a[x]] = ++num[lef[a[x]]];
			continue;
		}
		if(bl[a[x]+1] == 1) {
			chbl[++chbl[0]] = num[rig[a[x]+1]];
			chbl[++chbl[0]] = num[rig[a[x]+1]+1];
			
			--cnt[num[rig[a[x]+1]]];
			++cnt[num[rig[a[x]+1]]+1];
			
			chbl[++chbl[0]] = rig[a[x]+1];
			chbl[++chbl[0]] = a[x];
			
			lef[rig[a[x]+1]] = x;
			rig[a[x]] = rig[a[x]+1];
			num[a[x]] = ++num[rig[a[x]]];
			continue;
		}
	}
	FOR(i, 1, 10) {
		//复刻1到10的答案; 
	}
	FOR(i, 1, chbl[0]) {
		lef[chbl[i]] = rig[chbl[i]] = bl[chbl[i]] = num[chbl[i]] = cnt[chbl[i]] = 0;
	}
    return res;
}

void add(int x) { 
    //类似以上的更新答案。 
}

int doit(int qnum, int x) { 
    int L = min(x*sq, n);
    int i = qnum, l = L+1, r = L; //初始化左右端点
    anss = 0;  
    for(; b[h[i].l] == x; ++i) {
        if(b[h[i].l] == b[h[i].r]) {   //同块 
            ans[h[i].id] = query(h[i].l, h[i].r);
            continue;
        }
        while(r < h[i].r) 
          add1(++r); //这里直接瞎搞就行了 
        int qwq = anss; 
        while(l > h[i].l) 
          add2(--l); //和上面的要分开处理 
        ans[h[i].id] = anss; 
        l = L+1;  
        anss = qwq;  
    }
    return i; //当前处理的序号 
}

int main() {
    n = read(), m = read();
    sq = n/sqrt(m*3/2);
    FOR(i, 1, n) { 
        a[i] = read(),  
        b[i] = (i-1)/sq+1;
    }
    FOR(i, 1, m) { 
        h[i].l = read(),  
        h[i].r = read(),
        h[i].id = i;
    }
    sort(h+1,h+m+1); 
    int qnum = 1;
    FOR(i, 1, b[n]) {  //处理每一个块内的询问
        qnum = doit(qnum, i);
    }
    FOR(i, 1, m) {
        out(ans[i]);
        puts("");
    }
	return 0; 
}
