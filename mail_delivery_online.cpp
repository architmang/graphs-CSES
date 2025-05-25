#include<bits/stdc++.h>
using namespace std;
 
#define int long long int
#define endl '\n'
typedef long long ll;
 
const int MOD = 1000000007;
 
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif
 
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(long double t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(unsigned int t) {cerr << t;}
 
template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
 
const int N = 2e5+1;
vector<int> adj[N];
vector<int> edges[N];
bool mark[N]{};
int degree[N]{};
 
int n,m;
 
vector<int> path;
 
// Euiler tour
void dfs(int node){
    while(degree[node] < (int)adj[node].size()){
        int child = adj[node][degree[node]];
        int edge = edges[node][degree[node]];
        degree[node]++;
        if (!mark[edge]){
            mark[edge]=true;
            dfs(child);
        }
    }
    path.push_back(node);
}
 
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
 
    cin>>n>>m;
    for (int i = 1; i <= m; i++) {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        // index all the edges
        edges[u].push_back(i);
        edges[v].push_back(i);
    }
    // check if all the nodes have even degree.
    for (int i = 1; i <= n; i++) {
        if (adj[i].size()%2!=0){
            cout<<"IMPOSSIBLE"<<endl;
            exit(0);
        }
    }
 
    dfs(1);
 
    // check if this circuit is connected.
    if ( (int)path.size() != m+1 ) 
        cout<<"IMPOSSIBLE"<<endl;
    else{
        for(int node: path) cout<<node<<" ";
    }
 
    return 0;
}