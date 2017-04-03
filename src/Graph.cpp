#include "Graph.h"

dijkstra_return** Graph::returns;
int* Graph::terminals;

Graph::Graph(int V, int T){
    this->V = V;
    this->T = T;
    adj = new list<iPair> [V+1];
}

Graph::~Graph(){
    for (int i = 1; i <= V; ++i){
        adj[i].clear();
    }
    delete [] adj;
}

void Graph::addEdge(int u, int v, int w){
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

list<iPair> Graph::getEdges(int v){
    return adj[v];
}

int Graph::get_n_vertices(){
    return V;
}

int Graph::get_n_terminals(){
    return T;
}

void Graph::printGraph(){
    for (int i = 1; i <= V; ++i){
        list<iPair>::iterator it;
        for (it=adj[i].begin(); it!=adj[i].end(); ++it){
            cout << (*it).first << "-";
        }
    }
    cout << endl;
}

void Graph::DFS(int v, int* visited){
    visited[v] = 1;
    list<iPair>::iterator i = adj[v].begin();
    for (int j=2;i != adj[v].end(); ++i, j++){
        if(visited[j] == 0)
            DFS_util(j, visited);
    }
}

void Graph::DFS_util(int u, int* visited){
    visited[u] = 1;
    list<iPair>::iterator i = adj[u].begin();
    for (; i!=adj[u].end(); i++){
        if (visited[(*i).first] == 0)
            DFS_util((*i).first, visited);
    }
}

int Graph::isConnected() {
    int* visited = new int [V+1];
    int connected = 1;
    for(int i=1;i<=V+1;i++) visited[i] = 0; 
    
    DFS(1, visited);
    
    for (int i=1; i<=V;i++){
        if (visited[i] == 0){
            connected = 0;
            break;
        }
    }

    delete [] visited;
    return connected;
}

Graph* Graph::getMetricClousure(){
    Graph *metric_clousure = new Graph(T, T);

    returns = new dijkstra_return*[T];

    for (int i = 0; i < T; ++i){
        int src = terminals[i];
        returns[i] = dijkstra_one_to_all(src);
        for (int j = i+1; j < T; ++j){
            int target = terminals[j];
            metric_clousure->addEdge(j+1, i+1, returns[i]->path_weights[target]);
        }
    }

    return metric_clousure;
}

dijkstra_return* Graph::dijkstra_one_to_all(int src){
    dijkstra_return* dijtr_ret = new dijkstra_return;
    dijtr_ret->path_weights = new int[V+1];
    dijtr_ret->prev = new int[V+1];

    dijtr_ret->prev[src]=-1;

    for (int i = 1; i <= V; ++i){
        dijtr_ret->path_weights[i] = INF;
    }
    dijtr_ret->path_weights[src] = 0;

    set<iPair> set_visited;

    vector<int> dist(V+1, INF);

    set_visited.insert(make_pair(0, src));
    dist[src] = 0;

    while (!set_visited.empty()){
        iPair tmp = (*set_visited.begin());
        set_visited.erase(set_visited.begin());

        int u = tmp.second;

        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = (*i).first;
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight){

                if (dist[v] != INF)
                    set_visited.erase(set_visited.find(make_pair(dist[v], v)));

                dist[v] = dist[u] + weight;
                dijtr_ret->path_weights[v] = dist[v];
                dijtr_ret->prev[v] = u;
                set_visited.insert(make_pair(dist[v], v));
            }
        }
    }

    return dijtr_ret;
}

Graph* Graph::primMST(){
    Graph* mst = new Graph(V, T);

    priority_queue< pair<int, int> , vector <pair<int, int> > , greater<pair<int, int> > > pq;

    int src = 1;

    vector<int> key(V+1, INF);

    vector<int> parent(V+1, -1);

    vector<bool> inMST(V+1, false);

    pq.push(make_pair(0, src));
    key[src] = 0;

    while (!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        if(inMST[u])
            continue;

        inMST[u] = true;  

        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i){
            int v = (*i).first;
            int weight = (*i).second;

            if (inMST[v] == false && key[v] > weight){
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }
    int total_weigth = 0;
    for (int i = 2; i <= V; ++i){
        mst->addEdge(parent[i], i, key[i]);
        total_weigth += key[i];
    }   
    cout << "Cost: " << total_weigth <<" | ";

    return mst;
}

void Graph::print_steiner(){
    cout << "Tree: " << terminals[0] << "-";
    for (int i = 0; i < T-1; ++i){
        findPath(returns[i]->prev, terminals[i+1]);
    }
    cout << endl;
}


void read_file(Graph** graph, char* file){
    string line;
    char c;
    int V,E,v,w,W, T, t;
    ifstream f;
    f.open(file);

    if(f.fail()){
        cout << "Fail to open " << file << endl;
        cout << "Aborting...." << endl; 
        exit(1);
    }

    getline(f,line);
    f >> line >> V;
    f >> line >> E;

    for (int i = 0; i < E+4; ++i){getline(f, line);}

    f >> line >> T;

    (*graph) = new Graph(V, T);
    Graph::terminals = new int[T];

    for (int i = 0; i < T; ++i){
        f >> c >> t;
        Graph::terminals[i] = t;
    }

    f.close();

    f.open(file);    

    getline(f,line);

    f >> line >> V;

    f >> line >> E;

    while(f >> c >> v >> w >> W)
        (*graph)->addEdge(v, w, W);
}

void findPath(int* parents, int src){
    if (parents[src]==-1)
        return;

    findPath(parents, parents[src]);

    cout << src << "-";
}

void delete_globals(){
    delete [] Graph::terminals;
    if(Graph::returns != NULL){
        for(size_t i=0; i<sizeof((*Graph::returns))/sizeof(Graph::returns[0]);i++){
            delete [] Graph::returns[i]->prev;
            delete [] Graph::returns[i]->path_weights;

            delete Graph::returns[i];
        }
        delete [] Graph::returns;
    }
}
