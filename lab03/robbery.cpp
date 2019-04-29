#include <iostream>
#include <queue>
#include <vector>
#include <stdlib.h>

using namespace std;

int N, M, green = 1, yellow = 0, red = 0;

struct edge {
    int edgeid;
    int v1;
    int v2;
    int weight;
    bool critical;
};

int comp(const void* a, const void* b) {
    edge *a1 = (edge *) a;
    edge *b1 = (edge *) b;
    return (a1->weight > b1->weight);
}

void Merge(edge* &e, int low, int high, int mid) {
    int i, j, k;
    edge temp[high-low+1];
    i = low;
    k = 0;
    j = mid + 1;

    while (i <= mid && j <= high) {
        if (e[i].weight < e[j].weight) {
            temp[k] = e[i];
            k++;
            i++;
        }
        else {
            temp[k] = e[j];
            k++;
            j++;
        }
    }

    while (i <= mid) {
        temp[k] = e[i];
        k++;
        i++;
    }

    while (j <= high) {
        temp[k] = e[j];
        k++;
        j++;
    }

    for (i = low; i <= high; i++) {
        e[i] = temp[i-low];
    }
}

void MergeSort(edge* &e, int low, int high) {
    int mid;
    if (low < high) {
        mid = (low+high)/2;
        MergeSort(e, low, mid);
        MergeSort(e, mid+1, high);
        Merge(e, low, high, mid);
    }
}

struct component {
    int componentid;
    int compsize;
    queue <int> vertices;
    void add(component comp, int* &vcomponents) {
        int v;
        compsize += comp.compsize;
        while(!comp.vertices.empty()) {
            v = comp.vertices.front();
            comp.vertices.pop();
            vertices.push(v);
            vcomponents[v] = componentid;
        }
    }
};

struct pairs {
    int edge;
    int verticle;
};

void addedge(edge edge, int* &vcomponents, component* &components, queue<pairs>* &paths) {
    int comp1 = vcomponents[edge.v1];
    int comp2 = vcomponents[edge.v2];
    if (components[comp1].compsize > components[comp2].compsize) {
        components[comp1].add(components[comp2], vcomponents);
    }
    else {
        components[comp2].add(components[comp1], vcomponents);
    }
    pairs newpair;
    newpair.edge = edge.edgeid;
    newpair.verticle = edge.v2;
    paths[edge.v1].push(newpair);
    newpair.edge = edge.edgeid;
    newpair.verticle = edge.v1;
    paths[edge.v2].push(newpair);
}

bool getcycleedges(int source, int destination, queue<pairs>* &paths, bool* &circleedges, int loopnode) {
    bool found;
    pairs p;
    queue<pairs> srcp = paths[source];
    while(!srcp.empty()) {
        p = srcp.front();
        if (p.verticle != loopnode) {
            if (p.verticle == destination) {
                circleedges[p.edge] = true;
                found = true;
                return found;
            }
            else {
                found = getcycleedges(p.verticle, destination, paths, circleedges, source);
                if (found) {
                    circleedges[p.edge] = true;
                    found = true;
                    return found;
                }
            }
        }
        srcp.pop();
    }
    return false;
}

int main() {
    int v1, v2, weight, mstedges = 1, prevweight;
    edge currentedge;
    bool flag;
    cin >> N;
    cin >> M;
    int* vcomponents = new int[N+1];
    edge* edges = new edge[M];
    component* components = new component[N+1];
    queue<pairs>* paths = new queue<pairs>[N+1];
    bool* circleedges = new bool[M];
    vector<edge> equalweights;
    for(int i=1; i<=N; i++) {
        vcomponents[i] = i;
        components[i].componentid = i;
        components[i].compsize = 1;
        components[i].vertices.push(i);
    }
    for(int i=0; i<M; i++) {
        cin >> v1;
        cin >> v2;
        cin >> weight;
        edges[i].edgeid = i;
        edges[i].v1 = v1;
        edges[i].v2 = v2;
        edges[i].weight = weight;
    }
    MergeSort(edges, 0, M-1);
    addedge(edges[0], vcomponents, components, paths);
    prevweight = edges[0].weight;
    edges[0].critical = true;
    equalweights.push_back(edges[0]);
    for(int i=1; i<M; i++) {
        currentedge = edges[i];
        if (vcomponents[currentedge.v1] == vcomponents[currentedge.v2]) {
            if(currentedge.weight != prevweight) {
            	prevweight = currentedge.weight;
                equalweights.clear();
                if(mstedges == N-1) break;
            }
            else {
                flag = getcycleedges(currentedge.v1, currentedge.v2, paths, circleedges, -1);
                if(flag) {
                    flag = false;
                    for(unsigned int j=0; j<equalweights.size(); j++) {
                        if(circleedges[equalweights[j].edgeid]) {
                            flag = true;
                            if(equalweights[j].critical) {
                                equalweights[j].critical = false;
                                yellow++;
                                green--;;
                            }
                            circleedges[equalweights[j].edgeid] = false;
                        }
                    }
                    if (flag) yellow++;
                }
            }
        }
        else {
            addedge(currentedge, vcomponents, components, paths);
            mstedges++;
            green++;
            if(currentedge.weight != prevweight) {
                prevweight = currentedge.weight;
                equalweights.clear();
            }
            edges[i].critical = true;
            equalweights.push_back(edges[i]);
        }
    }
    red = M - green - yellow;
    cout << green << endl << red << endl << yellow << endl;
    return 0;
}
