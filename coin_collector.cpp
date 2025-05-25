#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
vector<int> graph[100100];

int id = 0;
int sccCount = 0;

vector<int> ids;
vector<int> low;
vector<bool> onStack;
stack<int> st;

vector<int> scc_graph[100100];
vector<ll> scc_coins(100100, 0);
vector<int> scc_visited(100100, -1);
vector<int> scc_path;

void scc_dfs(int node)
{
    if (scc_visited[node] != -1) return;
    scc_visited[node] = 1;
    for(auto k: scc_graph[node])
    {
        scc_dfs(k);
    }
    scc_path.pb(node);
}

void dfs(int node)
{
    // tarjan's algo
    st.push(node);
    onStack[node] = true;
    ids[node] = low[node] = id++;

    // iterate over neighbors and callback
    for(auto g: graph[node])
    {
        if(ids[g] == -1)
            dfs(g);
        if(onStack[g] == true)
            low[node] = min(low[node], low[g]);
    }

    // if node starts SCC, keep popping stack
    if(low[node] == ids[node])
    {
        while(true)
        {
            int top = st.top();
            onStack[top] = false;
            low[top] = low[node];
            st.pop();
            if(top == node)
                break;
        }
        sccCount++;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<ll> coins(n+1, 0);
    ids.resize(n+1);
    low.resize(n+1);
    onStack.resize(n+1);

    for(int i=1; i<=n; i++)
    {
        low[i] = INT_MAX;
        ids[i] = -1;
        onStack[i] = false;
        cin >> coins[i];
    }
    for(int i=1; i<=m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].pb(b);
    }
    for(int i=1; i<=n; i++)
    {
        if(ids[i] == -1)
            dfs(i);
    }
    // cout << "sccCount " << sccCount << endl;
    // cout << "low-link vector is ";
    set<int> unique_scc;
    map<int, vector<int>> scc_map;
    for(int i=1; i<=n; i++)
    {
        unique_scc.insert(low[i]);
        // cout << low[i] << " ";
        scc_map[low[i]].pb(i);
        // map vector doesn't ned to be initialized
    }
    // for(auto it: scc_map)
    // {
    //     cout << endl;
    //     auto vec = it.second;
    //     for(auto k:vec)
    //     {
    //         cout << k << " ";
    //     }
    // }    
    for(int i=1; i<=n; i++)
    {
        scc_coins[low[i]] += coins[i];
        for(auto j: graph[i])
        {
            if(low[i] == low[j]) continue;
            else{
                scc_graph[low[i]].pb(low[j]);
            }
        }
    }
    // remove duplicates
    for(auto uni: unique_scc)
    {
        auto it = unique(scc_graph[uni].begin(), scc_graph[uni].end());
        scc_graph[uni].erase(it, scc_graph[uni].end());
    }
    for(auto uni: unique_scc)
    {
        if(scc_visited[uni] == -1)
            scc_dfs(uni);
    }
    // cout << endl;
    reverse(scc_path.begin(), scc_path.end());
    // for(auto node: scc_path)
    // {
    //     cout << node << " ";
    // }
    // apply dp over topo sort
    vector<ll> dp(100100, 0);
    ll answer = 0;
    for(int i: scc_path)
    {
        dp[i] = max(dp[i], scc_coins[i]);
        for(int j: scc_graph[i])
        {
            dp[j] = max(dp[j], dp[i] + scc_coins[j]);
        }
        answer = max(answer, dp[i]);
    }
    cout << answer << endl;
    return 0;
}