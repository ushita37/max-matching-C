#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED

#include <stdio.h>
#include "graph.h"

/* ****************** */
/* Depth-first search */
/* ****************** */

typedef struct
{
  int visited[MAXV];
  int predecessor[MAXV];
} dfs_info;

typedef struct{
    int q[MAXV];
    int first;
    int last;
} queue;

void initialize_search(graph *g, dfs_info *d_i)
{
  int i;
  for (i = 0; i < g->nvertices; i++)
  {
    d_i->visited[i] = 0;
    d_i->predecessor[i] = -1;
  }
  return;
}

void dfs(graph *g, dfs_info *d_i, int start) {
//    グラフ g において頂点 start を始点とする深さ優先探索を行う.頂点 start が g の頂点であることは事前条件
//    として仮定する.実行終了時に,頂点 i が訪問済であるとき,d_i->visited[i] の値は 1 であり,
//            d_i->predecessor[i] の値は頂点 i の先行頂点であるようにする.
    d_i->visited[start] = 1;    // 訪問済みの印
    int i = 0;
    for (; i < g->degree[start]; i++){ // 資料p.16参照
        int vertex = g->edges[start][i];
        if (d_i->visited[vertex] != 0) continue;
        d_i->predecessor[vertex] = start;
        dfs(g, d_i, vertex);
    }
    return;
}

void dfs_terminal(graph *g, dfs_info *d_i, int start, int end){
    d_i->visited[start] = 1;
    if(d_i->visited[end]) return;   // 終点に到達済みならreturn

    for (int i = 0; i < g->degree[start]; i++){ // 資料p.16参照
        int vertex = g->edges[start][i];
        if (d_i->visited[vertex] != 0) continue;
        d_i->predecessor[vertex] = start;
        dfs_terminal(g, d_i, vertex, end);
    }
    return;
}

void push(queue *q, int x){
    q->q[q->last] = x;
    q->last++;
}

int pop(queue *q){
    int x = q->q[q->first];
    q->first++;
    return x;
}

int is_empty(queue *q){
    return q->first == q->last;
}

void bfs(graph *g, dfs_info *d_i, int start){
    queue *q = (queue *)malloc(sizeof(queue));
    q->first = 0;
    q->last = 0;
    push(q, start);
    d_i->visited[start] = 1;
    while(!is_empty(q)){
        int u = pop(q);
        for(int i = 0; i < g->degree[u]; i++){
            int v = g->edges[u][i];
            if(d_i->visited[v] == 1) continue;
            d_i->visited[v] = 1;
            d_i->predecessor[v] = u;
            push(q, v);
        }
    }
}

void print_predecessors(graph *g, dfs_info *d_i)
{
  int i;
  for (i = 0; i < g->nvertices; i++)
  {
    printf("%d: predecessor[%d] = %d\n", i, i, d_i->predecessor[i]);
  }
  return;
}

void print_visited_vertices(graph *g, dfs_info *d_i)
{
  int i;
  for (i = 0; i < g->nvertices; i++)
  {
    printf("%d: visited[%d] = %d\n", i, i, d_i->visited[i]);
  }
  return;
}

#endif
