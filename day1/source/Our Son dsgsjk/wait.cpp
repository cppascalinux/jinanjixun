#include<bits/stdc++.h>
#define ll long long
#define mk make_pair
#define pb push_back
#define pa pair<int,int>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<"\n"
#define fir first
#define sec second
#define SZ(x) (x).size()
using namespace std;
inline int read(){int w=1,s=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();} while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();} return w*s;}
int l[55],r[55],w[55],b[55],sum[55];
int n,m,i,j,cnt2,cnt=0,now,val;
int main() {
	freopen("wait.in","r",stdin);
	freopen("wait.out","w",stdout);
	m=read(),n=read();
	for(i=1; i<=m; i++) {
		l[i]=read(),r[i]=read(),w[i]=read();
		b[++cnt]=l[i],b[++cnt]=r[i]+1;
	}
	sort(b+1,b+cnt+1);
	cnt2=1;
	for(i=2; i<=cnt; i++)
		if(b[i]!=b[cnt2])
			b[++cnt2]=b[i];
	for(i=1; i<=m; i++) {
		l[i]=lower_bound(b+1,b+cnt2+1,l[i])-b;
		r[i]=lower_bound(b+1,b+cnt2+1,r[i]+1)-b;
	}
	for(i=0; i<(1<<m); i++) {
		memset(sum,0,sizeof(sum));
		for(j=1; j<=m; j++) {
			if(w[j]==-1) {
				if((1<<j-1)&i)
					val=1;
				else
					val=0;
			} else
				val=w[j];
			if(val==1)
				sum[l[j]]++,sum[r[j]]--;
			else
				sum[l[j]]--,sum[r[j]]++;
		}
		now=0;
		for(j=1; j<=cnt2; j++) {
			now+=sum[j];
			if(abs(now)>=2)
				break;
		}
		if(j>cnt2) {
			for(j=1; j<=m; j++) {
				if(w[j]==-1) {
					if((1<<j-1)&i)
						printf("1 ");
					else
						printf("0 ");
				} else
					printf("%d ",w[j]);
			}
			return 0;
		}
	}
	puts("-1");
	return 0;
}

