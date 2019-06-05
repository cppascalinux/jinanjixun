#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=102019;
bool xuan[N]; char s1[N];
int n,k,m,len,ans,top,a[N],stk[N];
void check(){
	if(top!=n)return;
	for(int i=0;i<len;i++)a[i]=0;
	for(int i=1;i<=top;i++)
		for(int j=0;j<=len;j++)
			a[j]+=stk[i]>>j&1;
	for(int i=0;i<=len;i++)
		if(a[i]&1)return;//for(int i=1;i<=n;i++)cout<<stk[i]<<" ";cout<<endl;
	++ans;
}
void dfs(int pos){
	if(pos>n)return check(),void();
	for(int i=0;i<m;i++){
		bool w=0;
		if(i>stk[top])stk[++top]=i,w=1; 
		dfs(pos+1); 
		if(w==1)--top;
	}
}
int main()
{
	freopen("end.in","r",stdin);
	freopen("end.out","w",stdout);
	cin>>n>>k>>s1; len=strlen(s1);
	int er=1; m=0; stk[0]=-1;
	for(int i=len-1;i>=0;i--)
		m+=er*(s1[i]-'0'),er*=2;
	ans=0; dfs(1);
	cout<<ans<<endl;
	fclose(stdin); fclose(stdout);
	return 0;
}
