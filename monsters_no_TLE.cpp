#include<bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define pi pair<int, int>

vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};
// URDL

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    int si, sj;
    queue<vi> q;
    cin >> n >> m;
    vector<vector<char>> map(n, vector<char>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> map[i][j];
            if(map[i][j] == 'A') {
                si = i;
                sj = j;
            }
            if(map[i][j] == 'M') {
                q.push({i, j, 0});
            }
        }
    }

    vector<vector<int>> monst_dist(n, vector<int>(m, -1));
    int x, y;
    // Multi-source BFS for monsters
    while(!q.empty()) {
        auto top = q.front();
        q.pop();
        x = top[0];
        y = top[1];
        int steps = top[2];
        if(monst_dist[x][y] != -1) continue;
        monst_dist[x][y] = steps;
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && map[nx][ny] != '#') {
                if(monst_dist[nx][ny] == -1) {
                    q.push({nx, ny, steps + 1});
                }
            }
        }
    }

    vector<vector<int>> a_dist(n, vector<int>(m, -1));
    vector<vector<pi>> parent(n, vector<pi>(m, {-1, -1}));
    vector<vector<int>> move_dir(n, vector<int>(m, -1));
    
    bool escaped = false;
    int ex = -1, ey = -1;
    queue<vi> aq;
    aq.push({si, sj, 0});
    a_dist[si][sj] = 0;
   
    while(!aq.empty()) {
        auto vec = aq.front();
        aq.pop();
        x = vec[0];
        y = vec[1];
        int steps = vec[2];

        if(x == 0 || x == n - 1 || y == 0 || y == m - 1) {
            escaped = true;
            ex = x;
            ey = y;
            break;
        }

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && map[nx][ny] != '#' && a_dist[nx][ny] == -1) {
                if(monst_dist[nx][ny] == -1 || steps + 1 < monst_dist[nx][ny]) {
                    a_dist[nx][ny] = steps + 1;
                    parent[nx][ny] = {x, y};
                    move_dir[nx][ny] = i;
                    aq.push({nx, ny, steps + 1});
                }
            }
        }
    }
    
    if(escaped) {
        string path;
        int cx = ex, cy = ey;
        while(cx != si || cy != sj) {
            int d = move_dir[cx][cy];
            if(d == 0) path += 'U';
            else if(d == 1) path += 'R';
            else if(d == 2) path += 'D';
            else if(d == 3) path += 'L';
            pi p = parent[cx][cy];
            cx = p.first;
            cy = p.second;
        }
        reverse(path.begin(), path.end());
        cout << "YES\n" << path.size() << "\n" << path << "\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}