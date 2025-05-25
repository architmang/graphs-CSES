#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define pb push_back

#define FOR(i, a, b) for (int i = (a); i <= (b); i++)

/* SCC from BenQ */
struct SCC {
	int N;
	vector<vi> adj, radj;
	vi todo, comps, comp;
	vector<bool> vis;
	void init(int _N) {
		N = _N;
		adj.resize(N), radj.resize(N), comp = vi(N, -1), vis.resize(N);
	}
	void ae(int x, int y) { adj[x].pb(y), radj[y].pb(x); }
	void dfs(int x) {
		vis[x] = 1;
		for(auto y: adj[x]) 
            if (!vis[y]) dfs(y);
		todo.pb(x);
	}
	void dfs2(int x, int v) {
		comp[x] = v;
		for(auto y: radj[x]) 
            if (comp[y] == -1) dfs2(y, v);
	}
	void gen(int _N) {  // fills allComp
		FOR(i, 1, _N) 
            if (!vis[i]) dfs(i);
		reverse(todo.begin(), todo.end());
		for(auto x: todo) 
        {
            if (comp[x] == -1)
            {
                dfs2(x, x);
                comps.pb(x);
            }
        }
	}
};

const int maxn = 1e5 + 5;

int n, m;
SCC scc;          // scc
int value[maxn];  // value of each room
ll group[maxn];   // value in each SCC
vi rgraph[maxn];  // reverse graph
ll dp[maxn];

// calculates dp[i]
ll DP(int i) {
	if (dp[i]) return dp[i];
	// start at i
	dp[i] = group[i];
	// simulate traveling from another SCC to this SCC
	for(auto j: rgraph[i])
        dp[i] = max(dp[i], DP(j) + group[i]);
	return dp[i];
}

int main() {
	cin >> n >> m;
	scc.init(n + 1);
	FOR(i, 1, n) 
        cin >> value[i];
	while (m--) {
		int a, b;
		cin >> a >> b;
		scc.ae(a, b);
	}

	// generate SCC
	scc.gen(n);
	// set dp to 0
	fill(dp + 1, dp + n + 1, 0);
	// precompute group value for each SCC
	FOR(i, 1, n) group[scc.comp[i]] += value[i];
	// create reverse edges for SCC
	FOR(i, 1, n)
    {
        for (auto j: scc.adj[i])
        {
            if (scc.comp[i] == scc.comp[j]) continue;
            rgraph[scc.comp[j]].pb(scc.comp[i]);
        }
    }
	// find dp value for each SCC
	ll ans = 0;
	for(auto i: scc.comps)
        ans = max(ans, DP(i));

	cout << ans << '\n';
}