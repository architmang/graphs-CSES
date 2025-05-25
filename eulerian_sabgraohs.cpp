#include<bits/stdc++.h>
using namespace std;
 
typedef long long ll;
ll mod = 1e9 + 7; 

int n,m;
 
vector<int> graphs[100100];
 
signed main()
{
    cin>>n>>m;
    for (int i = 1; i <= m; i++) {
        int u,v;
        cin>>u>>v;
        graphs[u].push_back(v);
        graphs[v].push_back(u);
    }
    // check if all the nodes have even degree.
    for (int i = 1; i <= n; i++) {
        if (graphs[i].size()%2!=0){
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