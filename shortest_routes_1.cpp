#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
#define llp pair<ll, ll>

vector<llp> graph [100100];

// bfs : unweighted shortest path
// djikstra : weighted
// djikstra me it does not matter if the graph is directed or undirected

int main()
{
    int n, m;
    cin >> n >> m;
    for(int i=0; i<m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].pb({b, c});
    }

    if(n == 1)
    {
        cout << "0";
        return 0;
    }

    vector<ll> final(n+1, -1);         //  init with inf distance
    priority_queue<llp, vector<llp>, greater<llp>> q;  // gives minm

    q.push({0, 1});          // distance, node'
    final[1] = 0;

    while(!q.empty())
    {
        auto k = q.top();
        q.pop();

        int node = k.second;
        ll dist = k.first;

        if(final[node] < dist) continue; // early termination

        for(auto vec:graph[node])
        {
            int neigh = vec.first;
            ll len = vec.second;

            if(final[neigh] == -1 || final[neigh] > final[node] + len)
            {
                final[neigh] = final[node] + len;
                q.push({final[neigh], neigh});
            }
        }
    }
    for(int i=1; i<=n; i++)
    {
        cout << final[i] << " ";
    }
    return 0;
}