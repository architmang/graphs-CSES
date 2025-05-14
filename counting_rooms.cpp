#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int>> v{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int vis[1010][1010];
int n,m;

void dfs(vector<vector<char> > &map, int i, int j)
{
    vis[i][j] = 1;       // mark visited
    for(auto k:v)
    {
        int nx = i +k.first;
        int ny = j + k.second;

        if(nx<n && nx >=0 && ny<m && ny >=0)
        {
            if(vis[nx][ny] == 0 && map[nx][ny] == '.')
                dfs(map, nx, ny);
        }
    }
}

int main()
{
    cin >> n >> m;
    vector<vector<char> > map(n, vector<char>(m, '.'));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin >> map[i][j];
        }
    }

    memset(vis, 0, sizeof(vis));    // mark all unvisited

    int ans = 0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(vis[i][j] == 0 && map[i][j] == '.')      // if node unvisisted, perform dfs
            {
                ans++;
                dfs(map, i, j);
            }
        }
    }
    cout << ans;
    return 0;
}