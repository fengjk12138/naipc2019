#include <bits/stdc++.h>
using namespace std;
const int maxn=305;

const long long mod = (long long )1e9+7;
typedef long long ll;
int fa[maxn],n,m,b[maxn],root;
vector<int>son[maxn];
struct polynomial
{
    vector<vector<int>>function;
    vector<vector<int>>integrate;
    vector<int>split_point;
    int is_heap;
};
int son_min[maxn];
vector<int>indefinite_integral;
polynomial node[maxn];
int pos[maxn];
inline int _pow(ll a,ll b)
{
    long long sum = 1;
    while (b)
    {
        if (b & 1)
        {
            sum = (sum * a) % mod;
            b--;
        }
        b >>=1;
        a = a * a % mod;
    }
    return sum;
}

inline int inv(ll x)
{
    return _pow(x,mod-2);
}

int cal(const vector<int> &now,int num)
{
    ll ans = 0;
    ll x = 1;
    for (int i : now)
    {
        ans = (ans + (ll) i * x % mod) % mod;
        x = x * num % mod;
    }
    return ans;
}

vector<int> integrate(const vector<int> &function)
{
    vector<int>out;
    out.push_back(0);
    ll now=1;
    for(int i : function)
    {
        out.push_back((ll)i*inv(now)%mod);
        now++;
    }
    return out;
}

vector<int> multiply(const vector<int> &a, const vector<int> &b)
{
    vector<int>out(a.size()-1+b.size()-1+1,0);
    for(int i=0; i<a.size(); i++)
        for(int j=0; j<b.size(); j++)
        {
            out[i+j]=(out[i+j]+(ll)a[i]*b[j]%mod)%mod;
        }
    return out;
}

vector<int> multiply(const vector<vector<int>> &a)
{
    vector<int>out;
    out.push_back(1);
    for(int i=0; i<a.size(); i++)
    {
        out=multiply(out,a[i]);
    }
    return out;
}
bool cmp(int x,int y)
{
    return x>y;
}

void dfs(int x)
{

    son_min[x] = b[x];
    if (son[x].empty())
    {
        node[x].split_point.push_back(0);
        node[x].function.push_back(vector<int> {inv(b[x])});
        indefinite_integral = integrate(node[x].function[0]);
        int tmp = cal(indefinite_integral, b[x]);
        for (int &i : indefinite_integral)
        {
            i = (-i + mod) % mod;
        }
        indefinite_integral[0] += tmp;
        indefinite_integral[0] %= mod;
        node[x].integrate.push_back(indefinite_integral);
        node[x].is_heap = 1;
        return;
    }

    for (int i:son[x])
    {
        dfs(i);
        son_min[x] = min(son_min[x], son_min[i]);
    }
    vector<int> spilt;
    spilt.push_back(0);
    if (son_min[x] != b[x])
    {
        spilt.push_back(son_min[x]);
    }
    memset(pos, -1, sizeof(pos));

    for (int i : son[x])
    {
        for (int j = 0; j < node[i].split_point.size(); j++)
        {
            if (node[i].split_point[j] < son_min[x])
            {
                spilt.push_back(node[i].split_point[j]);
                if (pos[i] == -1)
                    pos[i] = j;
            }
        }
    }
    sort(spilt.begin(), spilt.end(), cmp);
    int len = unique(spilt.begin(), spilt.end()) - spilt.begin();
    for(int i=0; i<len; i++)
        node[x].split_point.push_back(spilt[i]);
    for (int i = 0; i < len; i++)
    {
        int now_p = spilt[i];
        vector<vector<int>> need_mul;
        for (int j : son[x])
        {
            if (now_p >= son_min[x])
                need_mul.push_back(vector<int> {0});
            else if (now_p >= node[j].split_point[pos[j]])
                need_mul.push_back(node[j].integrate[pos[j]]);
            else
            {
                pos[j]--;
                need_mul.push_back(node[j].integrate[pos[j]]);
            }
        }
        //cout<<x<<endl;
        node[x].function.push_back(multiply(need_mul));
    }

    for (int i = 0; i < len; i++)
    {
        for (int &j : node[x].function[i])
        {
            j = (ll) j * inv(b[x]) % mod;
        }

    }
    for (int i = 0; i < len; i++)
    {
        vector<int> tmp = integrate(node[x].function[i]);

        if (i != 0)
        {
            int suff = cal(node[x].integrate[i - 1], spilt[i - 1]);
            int now = cal(tmp, spilt[i - 1]);
            for (int &k:tmp)
            {
                k = (-k + mod) % mod;
            }
            tmp[0] = ((tmp[0] + suff) % mod + now) % mod;
        }
        else
        {
            int u = cal(tmp, b[x]);
            for (int &k:tmp)
            {
                k = (-k + mod) % mod;
            }
            tmp[0] += u;
            tmp[0] %= mod;
        }
        node[x].integrate.push_back(tmp);
    }
    node[x].is_heap = cal(node[x].integrate[node[x].integrate.size()-1], 0);

}


int main()
{
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>b[i]>>fa[i];
        son[fa[i]].push_back(i);
        if(fa[i]==0)
            root=i;
    }
    dfs(root);
    cout<<node[root].is_heap<<endl;
    return 0;
}
