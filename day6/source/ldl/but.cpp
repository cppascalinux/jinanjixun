#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=102018;
const double eps=1e-6,pi=acos(-1);
#define int long long
int n,top,pr; bool xuan[N];
struct Point{double x,y,val;}stk[N],p[N],v[N];
double cross(Point a,Point b,Point c,Point d){
	return (b.x-a.x)*(d.y-c.y)-(d.x-c.x)*(b.y-a.y);
}
double Dot(Point a,Point b,Point c,Point d){
	return (b.x-a.x)*(d.x-c.x)+(b.y-a.y)*(d.y-c.y);
}
double dis(Point a,Point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int dcmp(double a){
	if(fabs(a)<eps)return 0;
	if(a>0)return 1; return -1;
}
bool cmp(const Point &a,const Point &b){
	double tmp=cross(stk[1],a,stk[1],b);
	if(tmp>0)return 1;
	if(dcmp(tmp)==0 && dcmp(dis(a,stk[1])-dis(a,stk[2]))<0)return 1;
	return 0;
}
int tubao(){
	sort(stk+2,stk+top+1,cmp);
	p[1]=stk[1]; int tot=1;
	for(int i=2;i<=top;i++){
		if(tot>1 && cross(p[tot],p[tot-1],p[tot],stk[i])>0)return 0;
		p[++tot]=stk[i];
	}
/*	cout<<"top:"<<top<<endl;
	cout<<"-------------"<<endl;
	for(int i=1;i<=top;i++)cout<<stk[i].x<<" "<<stk[i].y<<" "<<stk[i].val<<endl;
	cout<<"-------------"<<endl;*/
	return 1;
}
double init(Point x,bool a){
	double sum=0; stk[top+1]=stk[1];
	for(int i=1;i<=top;i++)
		sum+=fabs(acos(Dot(x,stk[i],x,stk[i+1])/dis(x,stk[i])/dis(x,stk[i+1])));
	if(dcmp(sum-2*pi)==0)return x.val;
	return 0;
}
void work1(){
	cout<<"down:"<<endl;
	for(int i=1;i<=top;i++)
		cout<<stk[i].x<<" "<<stk[i].y<<" "<<stk[i].val<<endl;
	cout<<"init:"<<endl;
	for(int i=1;i<=n;i++){
		if(!xuan[i] && init(v[i],1))
			cout<<v[i].x<<" "<<v[i].y<<" "<<v[i].val<<endl;
	}
}
void calc(){
	int ans=0;
	for(int i=1;i<=n;i++){
		if(xuan[i])ans+=v[i].val;
		else ans+=init(v[i],0);
	}
	if(ans==45968)work1();
	pr=min(ans,pr);
}
void check(){
	top=0;
	for(int i=1;i<=n;i++){
//		cout<<xuan[i]<<" ";
		if(xuan[i]){
			stk[++top]=v[i];
			if(top>1 && stk[top].y<stk[1].y)swap(stk[1],stk[top]);
		}
	}//cout<<endl;
	if(!tubao())return;
	calc();
}
void dfs(int step,int x){//cout<<step<<endl;
	if(n-step+1<x)return;
	if(step>n){
		if(!x)check();
		return;
	}
	if(x>0)xuan[step]=1; dfs(step+1,x-1);
	xuan[step]=0; dfs(step+1,x);
}
#undef int
int main()
{
	freopen("but.in","r",stdin);
	freopen("but.out","w",stdout);
	#define int long long
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>v[i].x>>v[i].y>>v[i].val;
	for(int i=3;i<=n;i++){
		pr=1e16+7; dfs(1,i);//cout<<"xix"<<endl;
		if(pr<1e16)cout<<pr<<" ";
		else{
			for(int j=i;j<=n;j++)cout<<"-1 ";
			break;
		}
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
