#include<bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
// 8x8 square
int vis[9][9] = {0};
vector<pii> neigh = { {+2, +1}, {+2, -1}, {-2, +1}, {-2, -1}, {+1, +2}, {+1, -2}, {-1, +2}, {-1, -2} };

bool valid(int x, int y)
{
    if(x>=1 && x<=8 && y>=1 && y<=8 && vis[x][y] == 0) return true;
    return false;
}

int count_degree(int x, int y)
{
    int count = 0;
    for(int i=0; i<8; i++)
    {
        int nx = x + neigh[i].first;
        int ny = y + neigh[i].second;

        if(valid(nx, ny))
            count++;
    }
    return count;
}

// naive dfs won't neccesarily find a full knight's tour
// therefore backtracking
bool dfs(int move_count, int x, int y)
{
    vis[x][y] = move_count;
    // base condition
    if (move_count == 64)
        return true;

    // collect all valid next moves and sort them by degree
    // warnsdoff's heuristic
    vector<pair<int, pii>> next_moves;
    for(int i=0; i<8; i++)
    {
        int nx = x + neigh[i].first;
        int ny = y + neigh[i].second;

        if(valid(nx, ny))
        {
            int degree = count_degree(nx, ny);
            next_moves.push_back({degree, {nx,ny}});
        }
    }
    // sort by ascending degree
    // prefer nodes with fewer onward options
    sort(next_moves.begin(), next_moves.end());
    for(auto move: next_moves)
    {
        int nx = move.second.first;
        int ny = move.second.second;
        if(dfs(move_count+1, nx, ny)) return true;
    }
    // backtrack
    vis[x][y] = 0;
    return false;
}
int main()
{
    int x, y;
    cin >> x >> y;
    dfs(1, x, y);
    for(int i=1; i<=8; i++)
    {
        for(int j=1; j<=8; j++)
        {
            cout << vis[j][i] << " ";
        }
        cout << endl;
    }
    return 0;
}