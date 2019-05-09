#include <bits/stdc++.h>
using namespace std;
const int maxn = 2005;
typedef long double dl;
const long double eps = 1e-5;
typedef long long ll;
int q,y,c,num;
int var_num_modifier[105],var_num_inflation[15],var_num_price[15][105];
dl price[15][105],modifier[105],inflation[15];


struct GUASS
{
    vector<vector<dl>>equation;
    int numx,numq;
    vector<dl>ans;
    vector<bool>solvable;

    int cmp(dl x,dl y)
    {
        if(fabs(x-y)<=eps)
            return 0;
        if(x-y>eps)
            return 1;
        if(x-y<eps)
            return -1;
        return -2;
    }

    void solve()
    {
        numq=equation.size();
        numx=equation[0].size();
        for(int i=1;i<=num;i++)
            solvable.push_back(0),ans.push_back(-1);
        for(int i=0;i<numq;i++)
        {
            int line=-1,now=INT_MAX;
            for(int j=i;j<numq;j++)
            {
                for(int k=0;k<numx;k++)
                {
                    if( cmp ( equation[j][k], 0 )!=0 && k<now)
                    {
                        line=j;
                        now=k;
                        break;
                    }
                }
            }
            // cout<<line<<" "<<now<<endl;
            if(line==-1)
                break;
            swap(equation[i],equation[line]);
            for(int j=0;j<numq;j++)
            {
                if(j==i) continue;
                if( cmp (equation[j][now] , 0) == 0) continue;
                dl coefficient=-equation[j][now]/equation[i][now];
                for(int k=now;k<numx;k++)
                    equation[j][k]+=coefficient*equation[i][k];
            }
        }
        for(int i=numq-1;i>=0;i--)
        {
            int now=-1;
            for(int j=0;j<numx;j++)
                if(cmp(equation[i][j],0) !=0)
                {
                    now=j;
                    break;
                }
            if(now==-1)
                continue;
            dl ans_num=0;
            int is_solve=1;
            for(int j=now+1;j<numx-1;j++)
            {
                if(cmp(equation[i][j],0)!=0&&solvable[j]==0) {
                    is_solve = -1;
                    break;
                }
                ans_num+=equation[i][j]*ans[j];
            }
            ans_num+=equation[i][numx-1];
            if(is_solve==-1)
                continue;
            ans[now]=-ans_num/equation[i][now];
            solvable[now]=1;
        }

    }

};

GUASS nku;

int main()
{

    cin>>y>>c>>q;
    for(int i=1;i<y;i++)
    {
        cin>>inflation[i];
        if(inflation[i]<=-0.5)
            var_num_inflation[i]=++num;
    }
    for(int i=1;i<=y;i++)
        for(int j=1;j<=c;j++)
        {
            cin>>price[i][j];
            if(price[i][j]<=-0.5)
                var_num_price[i][j]=++num;
        }
    for(int i=1;i<=c;i++)
        var_num_modifier[i]=++num;

    for(int i=1;i<y;i++) {

        for (int j = 1; j <= c; j++) {
            vector<dl> tmp;
            dl my_const = 0;
            for (int k = 0; k <= num; k++)
                tmp.push_back(0);
            if (var_num_price[i][j])
                tmp[var_num_price[i][j] - 1] = 1;
            else my_const += log(price[i][j]);
            tmp[var_num_modifier[j]-1] = 1;
            if (var_num_inflation[i])
                tmp[var_num_inflation[i] - 1] = 1;
            else my_const += log(inflation[i]);
            if (var_num_price[i + 1][j])
                tmp[var_num_price[i + 1][j] - 1] = -1;
            else my_const -= log(price[i + 1][j]);

            tmp[num]=my_const;
            nku.equation.push_back(tmp);
        }

    }
   /* for(int i=0;i<=num;i++)
        cout<<nku.equation[0][i]<<" ";
    cout<<endl;*/
    nku.solve();
   // cout<<pow(M_E,nku.ans[3])<<endl;
    for(int i=1;i<=y;i++)
        for(int j=1;j<=c;j++)
            if(var_num_price[i][j])
            {
                if(nku.solvable[var_num_price[i][j]-1])
                    price[i][j]=pow(M_E,nku.ans[var_num_price[i][j]-1]);
            }
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        printf("%.8Lf\n",price[r][l]);
    }
    return 0;
}
