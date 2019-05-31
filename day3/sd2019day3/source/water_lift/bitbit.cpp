#include <bits/stdc++.h>
using namespace std;
int n, m;
bool mat[501][501];
int kuai[501][501], cnt;
bool added[501][501];
bool vis[501][501];
static const int dx[4] = {0, 1, 0, -1};
static const int dy[4] = {1, 0, -1, 0};
void dfs1(int i, int j, int id);
int fa[250001];
int getf(int x)
{
    return fa[x] = (fa[x] == x ? x : getf(fa[x]));
}
int main()
{
    freopen("bitbit.in", "r", stdin);
    freopen("bitbit.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            char x;
            cin >> x;
            mat[i][j] = x - '0';
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (mat[i][j] && !vis[i][j])
                dfs1(i, j, ++cnt);
        }
    }
    for (int i = 1; i <= cnt; i++)
    {
        fa[i] = i;
    }
    int minu = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int fir = 0, sec = 0, thd = 0, fut = 0, cnt = 0;
            for (int d = 0; d < 4; d++)
            {
                if (i + dx[d] >= 1 && i + dx[d] <= n && j + dy[d] >= 1 && j + dy[d] <= m && mat[i + dx[d]][j + dy[d]])
                {
                    if (getf(fir) == getf(kuai[i + dx[d]][j + dy[d]]) || getf(sec) == getf(kuai[i + dx[d]][j + dy[d]]) || getf(thd) == getf(kuai[i + dx[d]][j + dy[d]]) || getf(fut) == getf(kuai[i + dx[d]][j + dy[d]]))
                        continue;
                    if (!fir)
                    {
                        fir = kuai[i + dx[d]][j + dy[d]];
                        cnt = 1;
                    }
                    else if (!sec)
                    {
                        sec = kuai[i + dx[d]][j + dy[d]];
                        cnt = 2;
                    }
                    else if (!thd)
                    {
                        thd = kuai[i + dx[d]][j + dy[d]];
                        cnt = 3;
                    }
                    else if (!fut)
                    {
                        fut = kuai[i + dx[d]][j + dy[d]];
                        cnt = 4;
                    }
                }
            }
            if (cnt == 4)
            {
                added[i][j] = 1;
                minu++;
                mat[i][j] = 1;
                kuai[i][j] = fa[getf(fut)] = fa[getf(thd)] = fa[getf(sec)] = fa[getf(fir)];
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int fir = 0, sec = 0, thd = 0, fut = 0, cnt = 0;
            for (int d = 0; d < 4; d++)
            {
                if (i + dx[d] >= 1 && i + dx[d] <= n && j + dy[d] >= 1 && j + dy[d] <= m && mat[i + dx[d]][j + dy[d]])
                {
                    if (getf(fir) == getf(kuai[i + dx[d]][j + dy[d]]) || getf(sec) == getf(kuai[i + dx[d]][j + dy[d]]) || getf(thd) == getf(kuai[i + dx[d]][j + dy[d]]) || getf(fut) == getf(kuai[i + dx[d]][j + dy[d]]))
                        continue;
                    if (!fir)
                    {
                        fir = kuai[i + dx[d]][j + dy[d]];
                        cnt = 1;
                    }
                    else if (!sec)
                    {
                        sec = kuai[i + dx[d]][j + dy[d]];
                        cnt = 2;
                    }
                    else if (!thd)
                    {
                        thd = kuai[i + dx[d]][j + dy[d]];
                        cnt = 3;
                    }
                    else if (!fut)
                    {
                        fut = kuai[i + dx[d]][j + dy[d]];
                        cnt = 4;
                    }
                }
            }
            if (cnt == 3)
            {
                added[i][j] = 1;
                minu++;
                mat[i][j] = 1;
                kuai[i][j] = fa[getf(fut)] = fa[getf(thd)] = fa[getf(sec)] = fa[getf(fir)];
                fa[0] = 0;
            }
        }
    }
    int plus = 0;
    for (int i = 1; i <= cnt; i++)
    {
        if (fa[i] == i)
            plus++;
    }
    cout << plus + minu << endl;
    for (int x = 1; x <= cnt; x++)
    {
        if (fa[x] == x)
        {
            cout << "+" << endl;
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (mat[i][j] && getf(kuai[i][j]) == fa[x])
                    {
                        cout << "1";
                    }
                    else
                    {
                        cout << "0";
                    }
                }
                cout << endl;
            }
        }
    }
    for (int x = 1; x <= minu; x++)
    {
        cout << "-" << endl;
        bool flag = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (!flag && added[i][j])
                {
                    cout << "1";
                    flag = 1;
                    added[i][j] = 0;
                }
                else
                {
                    cout << "0";
                }
            }
            cout << endl;
        }
    }
}
void dfs1(int x, int y, int id)
{
    kuai[x][y] = id;
    for (int i = 0; i < 4; i++)
    {
        if (x + dx[i] >= 1 && x + dx[i] <= n && y + dy[i] >= 1 && y + dy[i] <= m && mat[x + dx[i]][y + dy[i]] && !vis[x + dx[i]][y + dy[i]])
        {
            vis[x + dx[i]][y + dy[i]] = 1;
            dfs1(x + dx[i], y + dy[i], id);
        }
    }
}