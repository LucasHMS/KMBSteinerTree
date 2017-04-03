#include "Graph.h"

int main(int argc, char *argv[]){
    if(argc == 1 || argc > 2){
        cout << "Command line format: ./exe [input_graph.stp]" << endl;
        cout << "Aborting...." << endl;
        
        delete_globals();

        return 0;
    }

    clock_t c1, c2;
    Graph* input_graph = NULL;

    read_file(&input_graph, argv[1]); //just file reading, no preprocessing

    c1 = clock();

    // Check if the graph is disconnected, if it is, there is no Steiner Tree to be computed
    if(input_graph->isConnected() == 0){
        cout << "Disconnected Graph!\nAborting...." << endl;
        
        c2 = clock();
        double time = (1.0*(c2-c1))/CLOCKS_PER_SEC;
        cout << "Exec Time: " << time << endl;

        delete_globals();

        return 0;
    }

    // Check if all vertices are terminals, it they are, MST is the optimal Steiner Tree
    if(input_graph->get_n_vertices() == input_graph->get_n_terminals()){
        Graph* mst = input_graph->primMST();
        mst->printGraph();
        
        c2 = clock();
        double time = (1.0*(c2-c1))/CLOCKS_PER_SEC;
        cout << "Exec Time: " << time << endl;

        delete_globals();

        return 0;
    }

    // Check if there are only two terminals on the Graph, if there is, the shortest path between them is the answer
    else if(input_graph->get_n_terminals() == 2){
        dijkstra_return** ret = new dijkstra_return*[1];
        ret[0] = input_graph->dijkstra_one_to_all(Graph::terminals[0]);
        cout << "Cost: " << ret[0]->path_weights[Graph::terminals[1]] << " | ";
        
        cout << "Tree: " << Graph::terminals[0] << "-";
        findPath(ret[0]->prev, Graph::terminals[1]);
        cout << endl;

        c2 = clock();
        double time = (1.0*(c2-c1))/CLOCKS_PER_SEC;
        cout << "Exec Time: " << time << endl;

        delete_globals();

        return 0;
    }

    // Check if there are only one terminal, if there is, the Steiner Tree is only one vertex and cost 0
    else if(input_graph->get_n_terminals() == 1){
        cout << "Cost: 0 | " << "Tree: " <<Graph::terminals[0] << endl;

        c2 = clock();
        double time = (1.0*(c2-c1))/CLOCKS_PER_SEC;
        cout << "Exec Time: " << time << endl;

        delete_globals();
        return 0;
    }

    Graph* metric_clousure = input_graph->getMetricClousure(); // compute the metric closure of the graph

    Graph* mst = metric_clousure->primMST(); // from the given metric closure, compute the MST

    mst->print_steiner();  // from the MST, print the approximated Steiner Tree

    c2 = clock();

    double time = (1.0*(c2-c1))/CLOCKS_PER_SEC;

    cout << "Exec Time: " <<  time << endl;
    
    delete_globals();

    return 0;
}
