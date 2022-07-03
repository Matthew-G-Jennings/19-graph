#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void){
    graph g;
    int size, node1, node2;

    scanf("%d", &size);
    fprintf(stderr, "Creating graph of size %d\n", size);
    g = graph_new(size, 1);

    fprintf(stderr, "Getting edges...\n");
    while(1==scanf("%d", &node1)){
        if (1==scanf("%d", &node2)){
            fprintf(stderr, "n1=%d n2=%d\n", node1, node2);
            g = graph_add_edge(g, node1, node2);
        } else {
            fprintf(stderr, "Unmatched edges, exiting\n");
            return EXIT_FAILURE;
        }
    }
    fprintf(stderr, "Edges successfully set\n");

    graph_print_db(g);

    graph_print_adj(g);

    graph_bfs(g, 1);

    graph_dfs(g);

    g = graph_free(g);

    return EXIT_SUCCESS;
}