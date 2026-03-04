#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>

const int MAXN=1000005;

int n,m,dfsn[MAXN],low[MAXN],tag,rep[MAXN];
std::vector<int> list;
bool instack[MAXN];
std::stack<int> st;
//邻接表
struct Edge{
    int to,next;
}graph[MAXN];
int head[MAXN],cnt;

void add_edge(int u,int v);

// Tarjan
void tarjan(int u);
void findscc();

void read();

// 输出SCC数量和每个点的代表元
void printscc();

// 构建SCC-DAG,进行字典序最小拓扑排序
std::vector<int> dag_topo();

// 输出拓扑序
void printtopoorder(const std::vector<int>& topoorder);

int main(){ 
    read();
    findscc();
    printscc();
    std::vector<int> topoorder = dag_topo();
    printtopoorder(topoorder);
    return 0;
}

void add_edge(int u,int v){
    graph[++cnt].to=v;
    graph[cnt].next=head[u];
    head[u]=cnt;
}

void tarjan(int u){
    dfsn[u]=low[u]=++tag;
    st.push(u);
    instack[u]=true;

    for(int i=head[u];i;i=graph[i].next){
        int v=graph[i].to;
        if(!dfsn[v]){
            tarjan(v);
            low[u]=std::min(low[u],low[v]);
        }else if(instack[v]){
            low[u]=std::min(low[u],dfsn[v]);
        }
    }

    if(dfsn[u]==low[u]){
        int minnode=u;
        std::vector<int> component;
        int v;
        do{
            v=st.top();
            st.pop();
            instack[v]=false;
            component.push_back(v);
            if(v<minnode)minnode=v;
        }while(v!=u);
        for(int node:component) rep[node]=minnode;
        list.push_back(minnode);
    }
}

void read(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v);
    }
}

void findscc(){
    for(int i=1;i<=n;i++){
        if(!dfsn[i]) tarjan(i);
    }
}

void printscc(){
    int k=list.size();
    printf("%d\n",k);

    for(int i=1;i<=n;i++){
        printf("%d",rep[i]);
        if(i<n)printf(" ");
    }
    printf("\n");
}

std::vector<int> dag_topo(){
    std::vector<std::set<int>> dag(n+1);
    std::vector<int> indegree(n+1);

    // DAG
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=graph[i].next){
            int v=graph[i].to;
            int repu=rep[u],repv=rep[v];
            if(repu!=repv){
                if(dag[repu].insert(repv).second){
                    indegree[repv]++;
                }
            }
        }
    }

    // 拓扑排序
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    for(int r: list){
        if(!indegree[r]) pq.push(r);
    }

    std::vector<int> topoorder;
    while(!pq.empty()){
        int u=pq.top();
        pq.pop();
        topoorder.push_back(u);

        for(int v: dag[u]){
            indegree[v]--;
            if(!indegree[v]) pq.push(v);
        }
    }

    return topoorder;
}

void printtopoorder(const std::vector<int>& topoorder){
    int k=topoorder.size();
    for(int i=0;i<k;i++){
        printf("%d",topoorder[i]);
        if(i<k-1) printf(" ");
    }
    printf("\n");
}