#include<bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define pi pair<int, int>
#define endl "\n"

vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};
// URDL

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    int si, sj;
    queue<vi> q;
    cin >> n >> m;
    vector<vector<char> > map(n, vector<char>(m, '.'));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin >> map[i][j];
            if(map[i][j] == 'A')
            {
                si = i;
                sj = j;
            }
            if(map[i][j] == 'M')
            {
                q.push({i, j, 0});
            }
        }
    }
    vector<vector<int>> monst_dist(n+1, vector<int>(m+1, -1));

    int x, y;
    // multi source bfs
    while(!q.empty())
    {
        auto top = q.front();
        q.pop();
        x = top[0];
        y = top[1];
        int steps = top[2];
        monst_dist[x][y] = steps;

        for(int i=0; i<4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx >= 0 && nx < n && ny >= 0 && ny <m && map[nx][ny] != '#')
            {
                if(monst_dist[nx][ny] == -1)
                    q.push({nx, ny, steps+1});
            }
        }
    }

    vector<vector<int>> a_dist(n+1, vector<int>(m+1, -1)); // dist
    vector<vector<pi>> par(n+1, vector<pi>(m+1, {-1, -1})); // dir
    vector<vector<int>> dir(n+1, vector<int>(m+1, 0)); // par

   
    bool escaped = false;  // bfs for A
    while(!q.empty()) q.pop();
    q.push({si, sj, 0, 0}); // x, y, steps, direction
    a_dist[si][sj] = 0;
   
    while(!q.empty())
    {
        auto vec = q.front();
        q.pop();
        
        x = vec[0];
        y = vec[1];
        int steps = vec[2];
        int dirn = vec[3];
        
        a_dist[x][y] = steps;
        dir[x][y] = dirn;

        // check if A escaped
        if(x == 0 || x == n-1 || y == 0 || y == m-1)
        {
            escaped = true;
            break;
        }

        for(int i=0; i<4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny <m && map[nx][ny] != '#' && a_dist[nx][ny] == -1)
            {
                // if monster can't reach this cell or reaches after A
                if(monst_dist[nx][ny] == -1 || steps + 1 < monst_dist[nx][ny])
                {
                    par[nx][ny] = {x, y};
                    q.push({nx, ny, steps + 1, i});
                }
            }
        }
    }
    if(escaped)
    {
        string ret;
        int cnt = 0;
        int tx = x;
        int ty = y;
        while(tx!=si || ty!=sj)
        {
            cnt++;
            int d = dir[tx][ty];
            if( d == 0)   ret += 'U';
            else if(d == 1)   ret += 'R';
            else if(d == 2)   ret += 'D';
            else   ret += 'L';
            
            pi p = par[tx][ty];
            tx = p.first;
            ty = p.second;
        }
        reverse(ret.begin(), ret.end());
        cout << "YES" << endl << cnt << endl << ret << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
    return 0;
}