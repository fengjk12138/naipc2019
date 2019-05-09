#include<bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6+5;
const int mod = (int)1e9+7;
int a[maxn],p[maxn],n,m,k,l,s,t,r;
typedef long long ll;
int vis[maxn];
ll cal(int l,int r)
{
    if(l==r)
        return 1;
    int mid=(l+r)>>1;
    int now=++t;
    int u=0;
    for(int i=l;i<=mid;i++) {
        if(a[i]!=a[mid+i-l+1])
        {
            u=1;
            break;
        }
    }
    if(u==0)
        return 2ll*cal(l,mid)%mod;
    for(int i=l;i<=mid;i++)
        vis[a[i]]=now;
    for(int i=mid+1;i<=r;i++)
        if(vis[a[i]]==now)
            return 0;
    return cal(l,mid)*cal(mid+1,r)%mod;
}

int main()
{
    cin>>m>>n;
    for(int i=0;i<(1<<m);i++)
    {
        cin>>a[i];
       // cout<<a[i]<<endl;
    }
    ll ans=1;
    cout<<cal(0,(1<<m)-1)%mod;
    return 0;
