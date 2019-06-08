#include<cstdio>
#include<iostream>
#include<vector>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=1000000007;
int tree[101010],w[101010],fa[101010];
int n;
struct Node
{
    int l,r,i;
}a[101010],b[101010];
bool cmp(Node x,Node y)
{
    return x.l>y.l;
}
int ksm(int w,int x)
{
    int ans=1;
    while(x)
    {
        if(x&1)
            ans=(long long)ans*w%INF;
        x>>=1;
        w=(long long)w*w%INF;
    }
    return ans;
}
void update(int x)
{
    for(int i=x;i<=n;i+=i&-i)
        tree[i]++; 
}
int query(int x)
{
    int ans=0;
    for(int i=x;i;i-=i&-i)
        ans+=tree[i];
    return ans;
}
int find_set(int x)
{
    if(fa[x]==x)
        return x;
    return fa[x]=find_set(fa[x]);
}
int solve(Node *a)
{
    int i,xx;
    long long ans=0;
    memset(tree,0,sizeof(tree));
    memset(w,0,sizeof(w)); 
    for(i=1;i<=n;i++)
        fa[i]=i;
    sort(a+1,a+n+1,cmp);
    for(i=1;i<=n;i++)
    {
        xx=find_set(a[i].r);
        if(xx<a[i].l)
            return 0;
        fa[xx]=a[i].l-1;
        w[a[i].i]=xx;
    }
    for(i=1;i<=n;i++)
    {
        ans=(ans+query(w[i]))%2;
        update(w[i]);
    }
    if(ans%2==0)
        ans=1;
    else
        ans=INF-1;
    for(i=1;i<=n;i++)
        ans=ans*ksm(a[i].r-a[i].l+1,INF-2)%INF;
    return ans;
}
int main()
{
    freopen("determinant.in","r",stdin);
    freopen("determinant.out","w",stdout);
    int T,i,ans;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=1;i<=n;i++)
            scanf("%d%d%d%d",&a[i].l,&a[i].r,&b[i].l,&b[i].r),a[i].i=i,b[i].i=i;
        ans=(long long)solve(a)*solve(b)%INF;
        printf("%d\n",ans);
    }
    return 0;
}

