#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "mylib.h"
#include "queue2.h"

typedef enum { UNVISITED, VISITED_SELF, VISITED_DECENDANTS } state_t;

typedef enum { DIRECTED, UNDIRECTED } gtype_t;

static int step;

struct vertexrec{
    state_t state;
    int predecessor;
    int distance;
    int finish;
};

struct graphrec{
    int size;
    int **adj;
    gtype_t type;
    vertex *vert;
};

graph graph_new(int size, int type){
    int i;
    graph g = emalloc(sizeof *g);
    fprintf(stderr, "g alloced\n");

    g->size = size;

    g->adj = emalloc(sizeof g->adj[0] * size);
    fprintf(stderr, "g->adj alloced\n");

    g->vert = emalloc(sizeof g->vert[0] * size);
    fprintf(stderr, "g->vert alloced\n");

    for (i = 0; i < size; i++){
        g->adj[i] = emalloc(sizeof g->adj[0] * size);
        g->vert[i] = emalloc(sizeof g->vert[0]);
        g->vert[i]->state = UNVISITED;
        g->vert[i]->predecessor = -1;
        g->vert[i]->distance = -1;
        g->vert[i]->finish = 0;
    }
    fprintf(stderr, "g->adj[all] alloced\n");
    fprintf(stderr, "g->vert[properties] alloced\n");

    if (type == 1){
        g->type = DIRECTED;
    } else {
        g->type = UNDIRECTED;
    }
    return g;
}

graph graph_add_edge(graph g, int n1, int n2){
    g->adj[n1][n2] = 1;
    if(g->type == UNDIRECTED){
        g->adj[n2][n1] = 1;
    }
    return g;
}

void graph_bfs(graph g, int source){
    int i, u, v;
    queue q;
    q = queue_new();
    for(i = 0; i < g->size; i++){
        g->vert[i]->state = UNVISITED;
        g->vert[i]->distance = -1;
        g->vert[i]->predecessor = -1;
    }
    g->vert[source]->state = VISITED_SELF;
    g->vert[source]->distance = 0;
    enqueue(q, source);
    while(queue_size(q)>0){
        u = dequeue(q);
        for(v = 0; v < g->size; v++){
            if(g->adj[u][v] == 1 && g->vert[v]->state == UNVISITED){
                g->vert[v]->state = VISITED_SELF;
                g->vert[v]->distance = 1 + g->vert[u]->distance;
                g->vert[v]->predecessor = u;
                enqueue(q, v);
            }
        }
        g->vert[u]->state = VISITED_DECENDANTS;
    }
    printf("Breadth First Search\n");
    graph_print_vertices(g);
}

void graph_dfs(graph g){
    int v;
    for(v = 0; v < g->size; v++){
        g->vert[v]->state = UNVISITED;
        g->vert[v]->predecessor = -1;
    }
    step = 0;
    for(v = 0; v < g->size; v++){
        if(g->vert[v]->state == UNVISITED){
            visit(g, v);
        }
    }

    printf("Depth First Search\n");
    graph_print_vertices(g);
}

void visit(graph g, int v){
    int u;
    g->vert[v]->state = VISITED_SELF;
    step++;
    g->vert[v]->distance = step;
    for(u = 0; u < g->size; u++){
        if(g->adj[v][u] == 1 && g->vert[u]->state == UNVISITED){
            g->vert[u]->predecessor = v;
            visit(g, u);
        }
    }
    step++;
    g->vert[v]->state = VISITED_DECENDANTS;
    g->vert[v]->finish = step;
}

void graph_print_db(graph g){
    int i, j;
    fprintf(stderr, "Adjacency Matrix\n");
    for(i = 0; i < g->size; i++){
        for(j = 0; j < g->size; j++){
            fprintf(stderr, "%d ", g->adj[i][j]);
        }
        fprintf(stderr, "\n");
    }
}

void graph_print_adj(graph g){
    int i, j;
    printf("Adjacency List\n");
    for(i = 0; i < g->size; i++){
        printf("%d |", i);
        for(j = 0; j < g->size; j++){
            if(g->adj[i][j]){
                printf(" %d,", j);
            }
        }
        printf("\n");
    }
}

void graph_print_vertices(graph g){
    int i;
    printf("vertex dist predecessor finish\n");
    for(i = 0; i < g->size; i++){
        printf("   %d\t%d\t%d\t%d\n", i, g->vert[i]->distance, g->vert[i]->predecessor, g->vert[i]->finish);
    }
}

graph graph_free(graph g){
    int i;
    for(i = 0; i < g->size; i++){
        free(g->vert[i]);
        free(g->adj[i]);
    }
    free(g->vert);
    free(g->adj);
    free(g);
    return NULL;
}