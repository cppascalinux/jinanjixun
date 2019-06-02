#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<set>
#define re register
#define maxn 100000

int n,m,k,ans;
std::string s,t;
std::set<std::string> S;
int p[maxn+1];

int main(){
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	std::cin>>s>>m;
	n=s.size();
	for(re int i=0;i<n;++i)
		for(re int j=1;j<=n-i;++j)
			S.insert(s.substr(i,j));
	for(std::set<std::string>::iterator it=S.begin();it!=S.end();++it){
		t=*it;
		k=t.size();
		for(re int i=0;i<n;++i)
			p[i]=0;
		for(re int i=0;i<n-k;++i)
			if(s.substr(i,k)==t)
				for(re int j=i;j<i+k;++j)
					p[j]=1;
		re int res=0;
		for(re int i=0;i<=n;++i)
			res+=!i||(p[i]&&!p[i-1]);
		ans+=res==m;
	}
	std::cout<<ans;
	return 0;
}

