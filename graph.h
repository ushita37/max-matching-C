#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "graph_param.h"

/* *************** */
/* graph structure */
/* *************** */

typedef struct
{
  int edges[MAXV][MAXDEGREE]; /* adjacency info */
  int degree[MAXV];           /* outdegree of each vertex */
  int nvertices;              /* number of vertices in the graph */
  int nedges;                 /* number of edges in the graph */
} graph;

/* ****************************** */
/* functions for graph operations */
/* ****************************** */

void initialize_graph(graph *g)
{
  int i;
  g->nvertices = 0;
  g->nedges = 0;
  for (i = 0; i < MAXV; i++)
  {
    g->degree[i] = 0;
  }
  return;
}

void insert_vertex(graph *g)
{
  g->nvertices++;
  if (g->nvertices > MAXV)
    fprintf(stderr, "Warning: insertion exceeds max number of vertices\n");
  return;
}

int is_edge(graph *g, int x, int y)
{
  int i;
  for (i = 0; i < g->degree[x]; i++)
  {
    if (g->edges[x][i] == y)
    {
      return 1;
    }
  }
  return 0;
}

void insert_edge(graph *g, int x, int y)
{
  if (is_edge(g, x, y))
  {
    fprintf(stderr, "Warning: (%d, %d) already exists, no insertion is performed\n", x, y);
  }
  else
  {
    if (g->degree[x] >= MAXDEGREE)
    {
      fprintf(stderr, "Warning: insertion(%d, %d) exceeds max degree\n", x, y);
    }
    g->edges[x][g->degree[x]] = y;
    g->degree[x]++;
    g->nedges++;
  }
  return;
}

void read_graph(FILE *fp, graph *g)
{
  int i;
  int m;
  int x, y;

  initialize_graph(g);

  fscanf(fp, "%d %d\n", &(g->nvertices), &m);

  for (i = 0; i < m; i++)
  {
    fscanf(fp, "%d %d\n", &x, &y);
    insert_edge(g, x, y);
  }

  return;
}

void remove_edge(graph *g, int x, int y) {
    /** グラフ gにxを始点,yを終点とする辺があれば,それを取り除き,存在しなけれ
ば「存在しない」といメッセージを出力する関数.削除したときに,頂点xの出
次数が1だけ減少し,グラフgの辺数も1だけ減少する. **/
    if (is_edge(g, x, y)) {
        int i;
        for (i = 0; i < g->degree[x]; i++) {
            if (g->edges[x][i] == y)
                for (int j = i; j < g->degree[x] - 1; j++) {
                    g->edges[x][j] = g->edges[x][j + 1];
                }
            g->edges[x][g->degree[x]] = -1; // ダミー
        }
        g->degree[x]--;
        g->nedges--;
    } else fprintf(stderr, "Warning: (%d, %d) doesn't exists, no removal is performed\n", x, y);
    return;
}


void reorient_edge(graph *g, int x, int y) {
    /** グラフ gにxを始点,yを終点とする辺があれば,それを削除し,yを始点,xを終
  点とする辺を追加する関数. **/
    if (is_edge(g, x, y) && !is_edge(g, y, x)) {
        remove_edge(g, x, y);
        insert_edge(g, y, x);
    } else if (!is_edge(g, x, y)){
        //    グラフgにxを始点、yを終点とする辺がなければ、存在しないというメッセージ
        fprintf(stderr, "Warning: (%d, %d) doesn't exist, no reversal is performed\n", x, y);
    } else{
        // gにyを始点、xを終点とする辺が存在する時には、存在するというメッセージ
        fprintf(stderr, "Warning: the opposite direction (%d, %d) exists, no removal is performed\n", y, x);
    }
    return;
}

void print_graph(graph *g)
{
  int i, j;

  for (i = 0; i < g->nvertices; i++)
  {
    printf("%d:", i);
    for (j = 0; j < g->degree[i]; j++)
    {
      printf(" %d", g->edges[i][j]);
    }
    printf("\n");
  }
  return;
}

#endif
