#include <iostream>
#include <stdlib.h>
#include <list>
#include <stack>

using namespace std;

typedef long long int ll;

int N, d, sccnumber = 0;

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

struct scc {
    int size;
    bool isthisit;
};

scc strongconnectedcomponents[30001];
int sccid[30001];

class Graph {
public:
    int V;
    list<int> *adj;

    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void scchelper(int u, int disc[], int low[], stack<int> *st, bool stackMember[], int sccnumber) {
        static int time = 0;
        int w = 0;
        disc[u] = low[u] = ++time;
        st->push(u);
        stackMember[u] = true;
        list<int>::iterator i;
        for (i=adj[u].begin(); i!=adj[u].end(); i++) {
            int v = *i;
            if (disc[v] == -1) {
                scchelper(v, disc, low, st, stackMember, sccnumber);
                low[u]  = min(low[u], low[v]);
            }
            else if (stackMember[v] == true) {
                low[u]  = min(low[u], disc[v]);
            }
        }
        if (low[u] == disc[u]) {
            strongconnectedcomponents[sccnumber].size = 0;
            strongconnectedcomponents[sccnumber].isthisit = true;
            while (st->top() != u) {
                w = st->top();
                strongconnectedcomponents[sccnumber].size++;
                sccid[w] = sccnumber;
                stackMember[w] = false;
                st->pop();
            }
            w = st->top();
            strongconnectedcomponents[sccnumber].size++;
            sccid[w] = sccnumber;
            stackMember[w] = false;
            st->pop();
        }
    }

    void sccfinder() {
        int *disc = new int[V];
        int *low = new int[V];
        bool *stackMember = new bool[V];
        stack<int> *st = new stack<int>();
        for (int i=0; i<V; i++) {
            disc[i] = -1;
            low[i] = -1;
            stackMember[i] = false;
        }
        for (int i=0; i<V; i++) {
            if (disc[i] == -1) {
                scchelper(i, disc, low, st, stackMember, sccnumber);
                sccnumber++;
            }
        }
    }
};

int main()
{
    int v;
    N = readint();
    Graph g(N);
    for (int i=0; i<N; i++) {
        d = readint();
        for (int j=0; j<d; j++) {
            v = readint();
            v--;
            g.adj[v].push_back(i);
        }
    }
    g.sccfinder();
    for (int i=0; i<N; i++) {
        list<int>::iterator j;
        for (j=g.adj[i].begin(); j!=g.adj[i].end(); j++) {
            int v = *j;
            if (sccid[i] != sccid[v]) {
                strongconnectedcomponents[sccid[v]].isthisit = false;
            }
        }
    }
    for (int i=0; i<sccnumber; i++) {
        if (strongconnectedcomponents[i].isthisit) cout << strongconnectedcomponents[i].size << endl;
    }
}
