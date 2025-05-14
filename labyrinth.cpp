#include<bits/stdc++.h>
using namespace std;

//if you are using map, use macros
#define f first
#define s second 
#define mp make_pair 
#define ii pair<int, int>
#define pb push_back

vector<ii> v{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
// x refers t rows, y refers to columns
// d, u, r, l
int vis[1010][1010];
int n,m;
int prev_step[1010][1010];

int main()
{
    cin >> n >> m;
    vector<vector<char> > map(n, vector<char>(m, '.'));
    ii start, end;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin >> map[i][j];
            if(map[i][j] == 'A')
                start = mp(i, j);

            if(map[i][j] == 'B')
                end = mp(i, j);
        }
    }

    memset(vis, 0, sizeof(vis));    // mark all unvisited
    vis[start.f][start.s] = 1;
    queue<ii> q;
    q.push(start);
    // mark visited hen you encounter it the first time
    while(!q.empty())
    {
        auto node = q.front();
        q.pop();
        vis[node.f][node.s] = 1;

        for(int k=0; k<4; k++)
        {
            int nx = node.f + v[k].f;
            int ny = node.s + v[k].s;
            if(nx<n && nx >=0 && ny<m && ny >=0)
            {
                if(vis[nx][ny] == 0 && map[nx][ny] != '#')
                {
                    vis[nx][ny] = 1;
                    q.push({nx, ny});
                    prev_step[nx][ny] = k;
                }
            }
        }
    }

    if(vis[end.f][end.s])
    {
        cout << "YES" << "\n";
        ii curr = end;
        vector<int> dir;
        while(curr!=start)
        {
            int back = prev_step[curr.f][curr.s];
            dir.pb(back);
            curr.f = curr.f - v[back].f;
            curr.s = curr.s - v[back].s;
        }
        reverse(dir.begin(), dir.end());
        cout << dir.size() << "\n";
        for(auto g:dir)
        {
            if(g == 0) cout << "D";
            if(g == 1) cout << "U";
            if(g == 2) cout << "R";
            if(g == 3) cout << "L";
        }
    }
    else cout << "NO" << "\n";;
    return 0;
}