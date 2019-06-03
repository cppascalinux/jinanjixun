#include<bits/stdc++.h>
using namespace std;
struct vec{
	double x,y;
	vec(double x=0,double y=0):x(x),y(y){}
};
vec operator+(vec a,vec b){
	return vec(a.x+b.x,a.y+b.y);
}
vec operator-(vec a,vec b){
	return vec(a.x-b.x,a.y-b.y);
}
double operator*(vec a,vec b){
	return a.x*b.x+a.y*b.y;
}
double cross(vec a,vec b){
	return a.x*b.y-a.y*b.x;
}
double len(vec a){
	return sqrt(a*a);
}
double angle(vec a,vec b){
	return acos(a*b/len(a)/len(b));
}
int n;
vec points[51];
int w[51];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>points[i].x>>points[i].y>>w[i];
    }
}