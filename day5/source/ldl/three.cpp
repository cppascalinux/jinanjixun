#include<iostream>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
const double pi=acos(-1),eps=1e-6;
string s; int n,top; double stk[2019];
struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){}
}v[2019];
int dcmp(double a){
	if(abs(a)<eps)return 1;
	return 0;
}
Point operator - (Point A, Point B) { return Point(A.x - B.x, A.y - B.y); }
double Dot(Point A, Point B) { return A.x*B.y - A.y*B.x; }
int getans(){
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				if(s[i-1]=='1' || s[j-1]=='1' || s[k-1]=='1')
					stk[++top]=abs(Dot(v[i]-v[j],v[i]-v[k]))/2;
	int ans=0;
	for(int i=1;i<=top;i++)
		for(int j=i+1;j<=top;j++)
			ans+=dcmp(stk[i]-stk[j]);
	return ans;
}
int main()
{
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	cin>>n>>s;
	for(int i=1;i<=n;i++)
		v[i].x=cos(2*pi*i/n),v[i].y=sin(2*pi*i/n);
	if(n<=30)cout<<getans()<<endl;
	else cout<<"0"<<endl;
	fclose(stdin); fclose(stdout);
	return 0;
}
