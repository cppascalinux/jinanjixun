#include <algorithm>
#include <bitset>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define FOR(i, a, b) for(int i =(a); i <=(b); ++i)
#define FORD(i, a, b) for(int i = (a); i >= (b); --i)
#define REP(i, n) for(int i = 0;i <(n); ++i)
#define VAR(v, i) __typeof(i) v=(i)
#define FORE(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define PB push_back
#define MP make_pair
#define X first
#define Y second 
#define debug(x) {cerr <<#x <<" = " <<x <<endl; }
#define debugv(x) {{cerr <<#x <<" = "; FORE(itt, (x)) cerr <<*itt <<", "; cerr <<endl; }}
#define dprintf(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef vector<int> VI;

template<class C> void mini(C&a4, C b4){a4=min(a4, b4); }
template<class C> void maxi(C&a4, C b4){a4=max(a4, b4); }
template<class T1, class T2>
ostream& operator<< (ostream &out, pair<T1, T2> pair) { return out << "(" << pair.X << ", " << pair.Y << ")";}

const int MD = 12;
const int MX = 5e5+10;
int rgt[MD][MX];
int lft[MD][MX];



void solve() {
    int n;
    string S;
    cin >> S;
    n = SZ(S);
    REP(j,n+1)  {
        rgt[0][j] = j;
        lft[0][j] = j;
    }
    for (int c = 1; ; c++) {
        int x=c%12;
        REP(j,n+1) {
            rgt[x][j] = rgt[(c+11)%12][j];
            lft[x][j] = lft[(c+11)%12][j];
        }
        REP(j, n) {
            int cc = (c - S[j]+'0'+12)%12;
            if (cc < 0) continue;
            int l = lft[cc][j];
            int r = rgt[cc][j+1];
            mini(lft[x][r], l);
            maxi(rgt[x][l], r); 
        }

        FORD(j,n,1) mini(lft[x][j-1], lft[x][j]);
        REP(j,n) maxi(rgt[x][j+1], rgt[x][j]);

       // REP(j,n+1) cerr << MP(lft[c][j], rgt[c][j]) << " ";
       // cerr << endl;

        if (rgt[x][0] == n) {
            cout << c << endl;
            return;
        }
    }

}


int main(){
	freopen("guess.in","r",stdin);
	freopen("guess.out","w",stdout);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}

