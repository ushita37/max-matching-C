#ifndef BIPMATCHING_H_INCLUDED
#define BIPMATCHING_H_INCLUDED
#define BRUTE_FORCE_MAX 62

#include "dfs.h"

/* ************************** */
/* maximum-matching algorithm */
/* ************************** */

void construct_digraph_for_matching(graph *g) {
    int i, source, sink;
    source = g->nvertices;
    insert_vertex(g);
    sink = g->nvertices;
    insert_vertex(g);
    for (i = 0; i < g->nvertices - 2; i++) {
        if (g->degree[i] == 0) insert_edge(g, i, sink);
        else insert_edge(g, source, i);
    }
    return;
}

void augment(graph *g, dfs_info *d_i, graph *matching, int start, int end){
    int v = end, p = d_i->predecessor[v];
    while (v != start) {
        reorient_edge(g, p, v); // 有向道の全ての辺がgにおいて反転される
        if (v != end && p != start) { //  endとstartに接続している辺はmatchingに挿入したり、matchingから削除したりしない
            if (is_edge(matching, p, v) == 0 && is_edge(matching, v, p) == 0) {
                // matchingに u と v を結ぶ辺が存在しない場合
                insert_edge(matching, p, v);
            } else { // matchingに u と v を結ぶ辺が存在する場合
                remove_edge(matching, v, p); 
            }
        }
        v = p;
        p = d_i->predecessor[v];
    }
    return;
}


int find_maximum_matching(graph *g, graph *matching) {
    int size = 0;            /* the size of a current matching */
    int source, sink;
    dfs_info *d_i;
    source = g->nvertices - 2;
    sink = g->nvertices - 1;
    d_i = (dfs_info *) malloc(sizeof(dfs_info));

    initialize_search(g, d_i);
    dfs(g, d_i, source);    // sourceからsinkへ到達可能であるか(= 増加道が存在するか)調べる

    while (d_i->visited[sink]) {
        augment(g, d_i, matching, source, sink);
        size = matching->nedges;
        initialize_search(g, d_i);
        dfs(g, d_i, source);
    }

    return size;
}

int find_dfs_terminal(graph *g, graph *matching) {
    int size = 0;            /* the size of a current matching */
    int source, sink;
    dfs_info *d_i;

    source = g->nvertices - 2;
    sink = g->nvertices - 1;
    d_i = (dfs_info *) malloc(sizeof(dfs_info));

    initialize_search(g, d_i);
    dfs_terminal(g, d_i, source, sink);    // sourceからsinkへ到達可能であるか(= 増加道が存在するか)調べる

    while (d_i->visited[sink]) {
        augment(g, d_i, matching, source, sink);
        size = matching->nedges;
        initialize_search(g, d_i);
        dfs_terminal(g, d_i, source, sink);
    }

//    print_graph(matching);
    return size;
}


int find_bfs(graph *g, graph *matching) {   // 増加道アルゴリズムによって最大マッチングを発見する関数
    int size = 0;            /* the size of a current matching */
    int source, sink;
    dfs_info *d_i;

    source = g->nvertices - 2;
    sink = g->nvertices - 1;
    d_i = (dfs_info *) malloc(sizeof(dfs_info));

    initialize_search(g, d_i);
    bfs(g, d_i, source);    // sourceからsinkへ到達可能であるか(= 増加道が存在するか)調べる

    while (d_i->visited[sink]) {
        augment(g, d_i, matching, source, sink);
        size = matching->nedges;
        initialize_search(g, d_i);
        bfs(g, d_i, source);
    }

//    print_graph(matching);
    return size;
}

//typedef struct
//{
//    int edges[MAXV][MAXDEGREE]; /* adjacency info */
//    int degree[MAXV];           /* outdegree of each vertex */
//    int nvertices;              /* number of vertices in the graph */
//    int nedges;                 /* number of edges in the graph */
//} graph;

int is_matching(graph *matching) {
    // 出次数が高々1であることをチェック
    for (int i = 0; i < matching->nvertices; i++) {
        if (matching->degree[i] > 1) return 0;  // 出次数が1を超えるとマッチングの条件を満たさない
    }
    // 入次数が高々1であることをチェック
    int in_deg[matching->nvertices];
    for (int i = 0; i < matching->nvertices; i++) in_deg[i] = 0;    // initialize

    for (int i = 0; i < matching->nvertices; i++) {
        for (int j = 0; j < matching->degree[i]; j++) {
            int vertex = matching->edges[i][j];
            in_deg[vertex]++;
        }
    }
    for (int i = 0; i < matching->nvertices; i++) {
        if (in_deg[i] > 1) return 0;    // 入次数が1を超えるとマッチングは成立しない
    }

    return 1;
}

void construct_subgraph(graph *g, graph *g_sub, int e_subset[][2], int subset_cnt) {
    initialize_graph(g_sub);
    g_sub->nvertices = g->nvertices;

    for (int i = 0; i < subset_cnt; i++) {
        insert_edge(g_sub, e_subset[i][0], e_subset[i][1]);
    }
}


int find_brute_force(graph *g) {    // 力ずく法
    // graph *matchingは使わない
    if (g->nedges > BRUTE_FORCE_MAX) {
        fprintf(stderr, "input is too large to execute brute force.\n");
        exit(1);
    }

    int s = 0;  // 最終的に出力される最大マッチングの要素数を初期化
    // 部分集合を得る
    // 準備: 辺集合を全て取得
    int e_set[g->nedges][2];    // [i][0]は始点, [i][1]は終点
    long long e_count = 0;
    for (int i = 0; i < g->nvertices; i++) {
        for (int j = 0; j < g->degree[i]; j++) {
            e_set[e_count][0] = i;
            e_set[e_count][1] = g->edges[i][j];
            e_count++;
        }
    }

    // ビット全探索
    int size = 0;
    int e_subset[g->nedges][2];
    int subset_cnt;
    for (long long bit = 0; bit < (1 << e_count); bit++) {  // ステップ2: for each (M = Eの部分集合)

        subset_cnt = 0;
        for (long long i = 0; i < e_count; i++) {     // iはe_subsetの辺が何番目であるかを示す
            if (bit & (1 << i)) {  // 列挙にi番目の辺が含まれるか
                e_subset[subset_cnt][0] = e_set[i][0];
                e_subset[subset_cnt][1] = e_set[i][1];
                subset_cnt++;
            }
        }

        graph *g_sub = (graph *)malloc(sizeof(graph));
        construct_subgraph(g, g_sub, e_subset, subset_cnt);
        if (is_matching(g_sub) && g_sub->nedges > size) {
            size = g_sub->nedges;   // ステップ2-1
        }
        free(g_sub);    // メモリリーク対策
    }
    return size;
}


int find_greedy(graph *g, graph *matching) {
    // 準備: 辺集合を全て取得
    int e_set[g->nedges][2];    // [i][0]は始点, [i][1]は終点
    int e_count = 0;
    for (int i = 0; i < g->nvertices; i++) {
        for (int j = 0; j < g->degree[i]; j++) {
            e_set[e_count][0] = i;
            e_set[e_count][1] = g->edges[i][j];
            e_count++;
        }
    }

    for(int i = 0; i < e_count; i++){   // ステップ2: for each (e = Eの要素)
        insert_edge(matching, e_set[i][0], e_set[i][1]);
        if (is_matching(matching)) ;    // ステップ2-1: if (M U {e}がマッチングである)
        else remove_edge(matching, e_set[i][0], e_set[i][1]);

    }
    return matching->nedges;
}

#endif
