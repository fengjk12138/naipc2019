//
// Created by bob on 2019/5/9.
//
#include <bits/stdc++.h>
using namespace std;
const int maxn= (int)2e5+5;
struct edge
{
    int from,to,cap;
};
vector<int>ans;
vector<edge>G;
vector<int>graph[maxn];
int cur[maxn];
int S,T;
int n,m,k,l,s,t,r;
int dis[maxn];
bool is_end[maxn],is_begin[maxn];
inline void add_edge(int from,int to,int cap)
{
    G.push_back(edge{from,to,cap});
    graph[from].push_back(G.size()-1);
    G.push_back(edge{to,from,0});
    graph[to].push_back(G.size()-1);
}

int bfs()
{
    memset(dis,0, sizeof(dis));
    queue<int>q;
    dis[S]=1;
    q.push(S);
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        //cout<<now<<endl;
        for(int i : graph[now])
        {

            if(!dis[G[i].to]&&G[i].cap>0)
            {
                dis[G[i].to]=dis[now]+1;
                q.push(G[i].to);
            }
        }
    }
    return dis[T];
}

int dfs(int now,int max_flow)
{
    if(now==T)
        return max_flow;
    for(int &k = cur[now];k<graph[now].size();k++)
    {
        int i=graph[now][k];

        if(G[i].cap>0&&dis[G[i].to]==dis[now]+1) {
            int flow = dfs(G[i].to, min(max_flow, G[i].cap));
            if (flow) {
                G[i].cap-=flow;
                G[i^1].cap+=flow;
                return flow;
            }
        }
    }
    return 0;
}


int dinic()
{
    int ans=0;

    for(int i=1;i<=n;i++)
        add_edge(S,i,1),add_edge(i+n,T,1);
    while(bfs())
    {
        memset(cur,0, sizeof(cur));
        while(int flow = dfs(S,INT_MAX))
           ans+=flow;
    }


    return ans;
}




void bfs_end()
{
    is_end[S]=is_end[T]=1;
    queue<int>q;
    q.push(S);
    while (!q.empty())
    {
        int now=q.front();
        q.pop();
        for(int i : graph[now])
        {
            if(G[i].cap==1&&!is_end[G[i].to])
            {
                is_end[G[i].to]=1;
                q.push(G[i].to);
            }
        }

    }
}

void bfs_begin()
{
    queue<int>q;
    is_begin[S]=is_begin[T]=1;
    q.push(T);
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        for(int i : graph[now])
        {
            if(G[i].cap==0&&!is_begin[G[i].to])
            {
                is_begin[G[i].to]=1;
                q.push(G[i].to);
            }

        }

    }


}


int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    S=0,T=2*n+1;
    for(int i=1;i<=m;i++)
    {
        cin>>l>>r;
        add_edge(l,r+n,1);
    }
    int u=n-1-dinic();
    if(u)
        cout<<u<<endl;
    else
    {
        cout<<u<<endl<<endl;
        return 0;
    }

    bfs_end();
    bfs_begin();
    for(int i=1;i<=n;i++)
    {
        if(is_end[i]==1||is_begin[i+n])
            ans.push_back(i);
    }

    sort(ans.begin(),ans.end());
    for(int i:ans)
        cout<<i<<" ";
    cout<<endl;
    //cerr<<(double)clock()/CLOCKS_PER_SEC<<endl;
    return 0;
}
