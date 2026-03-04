#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cstring>
#include <functional>

#define ll long long
const int MAXM = 600010;  // m 的最大值
const int MAXN = 200010;  // n 的最大值
const int HEIGHT = 20;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int l[MAXM], r[MAXM];
ll c[MAXM];
std::tuple<ll,int,int,int> edges[MAXM]; // (weight,u,v,id)
bool inForest[MAXM];
bool intree[MAXM];

//并查集
int parent[MAXN],rk[MAXN];

void initDSU(int n);
int find(int x);
bool merge(int x,int y);

//邻接表
struct Edge{
    int to,next;
    ll weight;
}graph[MAXN*2];
int head[MAXN],cnt;

void addEdge(int from,int to,ll weight);

//LCA
int depth[MAXN],ancestor[HEIGHT][MAXN];
ll minWeight[HEIGHT][MAXN];
bool visited[MAXN];

void dfs(int u, int p, int d, ll w);
void LCA(int n);

//kruskal
void kruskal(int m, int n);
void preprocess(int m);
ll query(int u,int v);

void read(int m);
void queries(int q);

int main(){ 
    int m,n,q;
    scanf("%d %d",&m,&n);
    
    read(m);
    kruskal(m, n);
    LCA(n);
    preprocess(m);
    
    scanf("%d",&q);
    queries(q);

    return 0;
}



void initDSU(int n) {
    for(int i=0;i<=n+1;i++){
        parent[i]=i;
        rk[i]=0;
    }
}

void read(int m) {
    for(int i=1;i<=m;i++){
        int u,v;
        ll weight;
        scanf("%d %d %lld",&u,&v,&weight);
        l[i]=u,r[i]=v,c[i]=weight;
        edges[i]=std::make_tuple(weight,u,v+1,i);
    }
}

void kruskal(int m, int n) {
    initDSU(n);
    
    std::sort(edges+1,edges+m+1,std::greater<std::tuple<ll,int,int,int>>());

    // Kruskal
    for(int i=1;i<=m;i++){
        auto& [weight,u,v,id]=edges[i];
        if(merge(u,v)){
            inForest[id]=true;
            addEdge(u,v,weight);
            addEdge(v,u,weight);
        }
    }

    // 重新初始化并查集用于连通性查询
    initDSU(n);
    for(int i=1;i<=m;i++){
        if(inForest[i]) merge(l[i],r[i]+1);
    }
}

void LCA(int n) {
    //初始化LCA数组
    memset(ancestor,-1,sizeof(ancestor));
    memset(visited,0,sizeof(visited));

    //dfs
    for(int i=1;i<=n+1;i++){
        if(!visited[i]&&head[i]!=0) dfs(i, -1, 0, INF);
    }

    //处理孤立点
    for(int i=1;i<=n+1;i++){
        if(!visited[i]) {
            visited[i]=true;
            depth[i]=0;
            ancestor[0][i]=-1;
            minWeight[0][i]=INF;
            for(int j=1;j<HEIGHT;j++){
                ancestor[j][i]=-1;
                minWeight[j][i]=INF;
            }
        }
    }
}

void preprocess(int m) {
    for(int i=1;i<=m;i++){
        if(inForest[i]) intree[i]=true;
        else {
            int u=l[i],v=r[i]+1;
            ll minedge=query(u,v);
            intree[i]=(minedge==c[i]);
        }
    }
}

void queries(int q) {

    for(int i=1;i<=q;i++){
        int k;
        scanf("%d",&k);
        if(intree[k]) printf("YES\n");
        else printf("NO\n");
    }
}

int find(int x){
    if(x!=parent[x]) parent[x]=find(parent[x]);
    return parent[x];
}

bool merge(int x,int y){
    x=find(x),y=find(y);
    if(x==y) return false;
    if(rk[x]<rk[y]) std::swap(x,y); 
    parent[y]=x;
    if(rk[x]==rk[y]) rk[x]++;
    return true;
}

void addEdge(int from,int to,ll weight){
    graph[++cnt]={to,head[from],weight};
    head[from]=cnt;
}

void dfs(int u,int p,int d,ll w){
    visited[u]=true;
    depth[u]=d;
    ancestor[0][u]=p;
    minWeight[0][u]=w;
    
    for(int i=1;i<HEIGHT;i++){
        if(ancestor[i-1][u]!=-1){
            ancestor[i][u]=ancestor[i-1][ancestor[i-1][u]];
            minWeight[i][u]=std::min(minWeight[i-1][u], minWeight[i-1][ancestor[i-1][u]]);
        } else {
            ancestor[i][u]=-1;
            minWeight[i][u]=INF;
        }
    }
    
    for(int i=head[u];i;i=graph[i].next){
        int v=graph[i].to;
        ll weight=graph[i].weight;
        if(!visited[v]) dfs(v,u,d+1,weight);
    }
}

ll query(int u,int v){
    if(find(u)!=find(v)) return INF; 

    ll ans=INF;
    if(depth[u]<depth[v]) std::swap(u,v);

    int differ=depth[u]-depth[v];
    for(int i=0;i<HEIGHT;i++){
        if((differ>>i)&1){
            ans=std::min(ans,minWeight[i][u]);
            u=ancestor[i][u];
        }
    }

    if(u==v) return ans;

    for(int i=HEIGHT-1;i>=0;i--){
        if(ancestor[i][u]!=ancestor[i][v]){
            ans=std::min(ans,minWeight[i][u]);
            ans=std::min(ans,minWeight[i][v]);
            u=ancestor[i][u];
            v=ancestor[i][v];
        }
    }
    ans=std::min(ans,minWeight[0][u]);
    ans=std::min(ans,minWeight[0][v]);
    return ans;
}
