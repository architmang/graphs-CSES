#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
#define rep(i,a,b) for (int i=a; i<b; ++i)
const int mod = 1e9+7;

vector<int> adj[100005];
bool vis[100005];
vector<int> v;

void dfs(int s){
    if (vis[s]) return;
    vis[s]=1;
    for (auto i: adj[s]) dfs(i);
    v.pb(s);
}

int main(){
    int n,m; 
    cin >> n >> m;
    rep(i,0,m){
        int a,b; 
        cin >> a >> b;
        adj[b].pb(a);
    }
    rep(i,1,n+1){
        if (!vis[i]) dfs(i);
    }

    vector<int> t;
    int i=0,f=0;
    while(i<v.size()){
        if (f==0){
            if (v[i]==1) {f=1; t.pb(1);}
        }
        else{
            t.pb(v[i]);
        }
        i++;
    }
    int path[100005]={0};
    path[1]=1;
    for (auto i: t) {
        for (auto j: adj[i]){
            path[i] = (path[i] + path[j]) % mod;
        }
    }
    cout << path[n] << endl;;
    return 0;
}