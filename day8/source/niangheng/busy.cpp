#include<map>
#include<cmath>
#include<ctime>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#define qmin(x,y) (x=min(x,y))
#define qmax(x,y) (x=max(x,y))
#define mp(x,y) make_pair(x,y)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
struct io
{
	char ibuf[ 5000000 ] , * s , obuf[ 5000000 ] , * t;
	int a[24];
	io() : t( obuf )
	{
		freopen( "nh.in" , "r" , stdin );
		freopen( "zhy.out" , "w" , stdout );
		fread( s = ibuf , 1 ,  5000000  , stdin );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	inline int read()
	{
		register int u = 0;
		while( * s < 48 ) s++;
		while( * s > 32 )
			u = u * 10 + * s++ - 48;
		return u;
	}
	template < class T >
	inline void print( register T u )
	{
		static int * q = a;
		if( !u ) * t++ = 48;
		else
		{
			while( u ) * q++ = u % 10 + 48 , u /= 10;
			while( q != a )
				* t++ = * --q;
		}
		* t++ = '\n';
	}
} ip;

#define read ip.read
#define print ip.print
//inline int read(){
//    int ans=0,fh=1;
//    char ch=getchar();
//    while(ch<'0'||ch>'9'){
//        if(ch=='-') fh=-1;
//        ch=getchar();
//    }
//    while(ch>='0'&&ch<='9')
//        ans=ans*10+ch-'0',ch=getchar();
//    return ans*fh;
//}
const int maxn=1e5+100,inf=0x7fffffff,maxd=400;
const ull base1=233333,base2=19260817;
int n,m,a[maxn],M,bl[maxd],br[maxd],dd[maxn],blk;
//int lx[maxd][maxn],rx[maxd][maxn];
map<int,int>lx[maxd],rx[maxd];
map<ull,int>mn[maxd];
inline ull bh(int x,int y){
	return base1*x+base2*y;
}
inline void prepare(){
	M=sqrt(n),blk=(n-1)/M+1;
	memset(bl,0x3f,sizeof(bl));
	for(int i=1;i<=n;i++){
		int x=dd[i]=(i-1)/M+1;
		qmin(bl[x],i),qmax(br[x],i);
	}
	for(int d=1;d<=blk;d++){
		int L=bl[d],R=br[d];
		for(int i=L;i<=R;i++){
			if(lx[d].find(a[i])==lx[d].end())
				lx[d][a[i]]=i;
			rx[d][a[i]]=i;
//			if(!lx[d][a[i]])
//				lx[d][a[i]]=i;
//			rx[d][a[i]]=i;
		}
		for(int i=L;i<=R;i++)
			for(int j=i+1;j<=R;j++){
				int x=a[i],y=a[j];if(x>y) swap(x,y);
				ull tmp=bh(x,y);
				if(mn[d].find(tmp)==mn[d].end())
					mn[d][tmp]=j-i;
				else qmin(mn[d][tmp],j-i);
			}
	}
}
inline int query(int x,int y){
	int ans=inf,Rx=-1,Ry=-1;
	for(int d=1;d<=blk;d++){
		int tx=Rx,ty=Ry;
		if(lx[d].find(x)!=lx[d].end()){
			if(~ty) qmin(ans,lx[d][x]-ty);
			Rx=rx[d][x];
		}
//		if(lx[d][x]){
//			if(~ty) qmin(ans,lx[d][x]-ty);
//			Rx=rx[d][x];
//		}
		if(lx[d].find(y)!=lx[d].end()){
			if(~tx) qmin(ans,lx[d][y]-tx);
			Ry=rx[d][y];
		}
//		if(lx[d][y]){
//			if(~tx) qmin(ans,lx[d][y]-tx);
//			Ry=rx[d][y];
//		}
		ull tmp=bh(x,y);
		if(mn[d].find(tmp)!=mn[d].end())
			qmin(ans,mn[d][tmp]);
	}
	return ans==inf?0:ans;
}
int main(){
	freopen("busy.in","r",stdin);
	freopen("busy.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	if(n<=1000&&m<=1000){
		int Ans=0;
		while(m--){
			int ms=read();
			int x=read()^Ans,y=read()^Ans;
			if(ms==1){
				for(int i=1;i<=n;i++)
					if(a[i]==x) a[i]=y;
			}
			else{
				int rx=-1,ry=-1;Ans=inf;
				for(int i=1;i<=n;i++){
					if(a[i]==x){
						if(~ry) qmin(Ans,i-ry);
						rx=i;
					}
					if(a[i]==y){
						if(~rx) qmin(Ans,i-rx);
						ry=i;
					}
				}
				if(Ans==inf) printf("Chtholly\n"),Ans=0;
				else printf("%d\n",Ans);
			}
		}
	}
	else{
		int Ans=0;
		prepare();
		while(m--){
			int ms=read();
			int x=read()^Ans,y=read()^Ans;
			if(x>y) swap(x,y);
			Ans=query(x,y);
			if(Ans) printf("%d\n",Ans);
			else puts("Chtholly");
		}
	}
    return 0;
}















