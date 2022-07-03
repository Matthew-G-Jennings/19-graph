#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>

typedef struct graphrec *graph;

typedef struct vertexrec *vertex;

extern graph graph_new(int size, int type);
extern graph graph_add_edge(graph g, int n1, int n2);
extern void graph_bfs(graph g, int source);
extern void graph_dfs(graph g);
extern void visit(graph g, int v);
extern void graph_print_vertices(graph g);
extern void graph_print_db(graph g);
extern void graph_print_adj(graph g);
extern graph graph_free(graph g);

#endif