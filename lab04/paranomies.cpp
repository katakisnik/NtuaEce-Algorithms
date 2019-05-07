#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

typedef pair<int, int> iPair;
int N, M, K, Q;
int distances[100][2000];

int readint() {
    int n = 0;
    char c = getchar_unlocked();
    while ( !( '0' <= c && c <= '9' ) ) {
    c = getchar_unlocked();
    }
    while ( '0' <= c && c <= '9' ) {
    n = n * 10 + c - '0';
    c = getchar_unlocked();
    }
    return n;
}

struct query {
    int src;
    int dest;
    int illegals;
};

query queries[10000];

class Graph
{
    int V;
    list< pair<int, int> > *adj;

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void shortestPath(int s);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair> [V];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
}

void Graph::shortestPath(int src)
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    //vector<int> dist(V, INF);
    pq.push(make_pair(0, src));
    distances[src][src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;
            if (distances[src][v] > distances[src][u] + weight)
            {
                distances[src][v] = distances[src][u] + weight;
                pq.push(make_pair(distances[src][v], v));
            }
        }
    }
}

int main()
{
    int u,v,w;
    //cin >> N >> M >> K >> Q;
    N = readint();
    M = readint();
    K = readint();
    Q = readint();
    Graph g(N*(K+1));
    for (int i=0; i<M; i++) {
        //cin >> u >> v >> w;
        u = readint();
        v = readint();
        w = readint();
        u--;
        v--;
        g.addEdge(u, v, w);
        for (int j=0; j<K; j++) {
            g.addEdge(u+(j+1)*N, v+(j+1)*N, w);
            g.addEdge(v+j*N, u+(j+1)*N, w);
        }
    }
    for (int i=0; i<N; i++) {
        for (int j=0; j<(N*(K+1)); j++) {
            distances[i][j] = INF;
        }
    }
    for (int i=0; i<N; i++) {
        g.shortestPath(i);
    }
    for (int i=0; i<Q; i++) {
        query q;
        //cin >> u >> v >> w;
        u = readint();
        v = readint();
        w = readint();
        u--;
        v--;
        q.src = u;
        q.dest = v;
        q.illegals = w;
        queries[i] = q;
    }
    for (int i=0; i<Q; i++) {
        query q = queries[i];
        int mina;
        mina = distances[q.src][q.dest];
        for (int j=1; j<q.illegals+1; j++) {
            if (distances[q.src][q.dest+j*N] < mina) {
                mina = distances[q.src][q.dest+j*N];
            }
        }
        if (mina == INF) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            cout << mina << endl;
        }
    }
    return 0;
}
