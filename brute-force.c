#include <stdio.h>
#include <stdlib.h>
#include "bipmatching.h"

int main(int argc, char *argv[]) {
    int size_matching;            /* the size of a matching */
    FILE *fp;
    graph *g;            /* a graph to analyze */
    graph *matching;            /* a matching to be found */
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "File open failed\n");
        fclose(fp);
        return 0;
    }
    g = (graph *) malloc(sizeof(graph));
    matching = (graph *) malloc(sizeof(graph));
    read_graph(fp, g);
    fclose(fp);

    size_matching = find_brute_force(g);  // graph *matchingは使わない
    printf("the maximum matching size = %d\n", size_matching);

    free(g);
    free(matching);
    return 0;
}