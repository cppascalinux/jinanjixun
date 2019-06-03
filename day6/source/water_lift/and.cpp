#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m;
int a[9],b[9];
int calc(int i){
    if(i==n+1){
        return 1;
    }
    int rtn=0;
    for(int x=0;x<(1<<m);x++){
        if(i==1||((x&b[i])>=(a[i-1]&b[i-1])&&(x|b[i])<=(a[i-1]|b[i-1]))){
            a[i]=x;
            rtn=(rtn+calc(i+1))%mod;
        }
    }
    return rtn%mod;
}
int main(){
    freopen("and.in","r",stdin);
    freopen("and.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>b[i];
    cout<<calc(1)<<endl;
}
