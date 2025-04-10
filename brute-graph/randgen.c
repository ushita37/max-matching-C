#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "../graph_param.h"

int mat[MAXV][MAXV];
int degx[MAXV];
int degy[MAXV];
int random_generation(int, int, double);

int random_generation(int size_x, int size_y, double p)
{
  int i, j;
  int nedges = 0;
  for(i = 0; i < size_x; i++) {
    degx[i] = 0;
  }
  for(j = 0; j < size_y; j++) {
    degy[j] = 0;
  }
  
  for(i = 0; i < size_x; i++) {
    for(j = 0; j < size_y; j++) {
      if(((double)rand())/((double)RAND_MAX) < p) {
        mat[i][j] = 1;
        degx[i]++;
        degy[j]++;
        nedges++;
        if(degx[i] > MAXDEGREE || degy[j] > MAXDEGREE) {
          fprintf(stderr, "Unfortunately, too many edges incident to a vertex\n");
          return 0;
        }
      } else {
        mat[i][j] = 0;
      }
    }
  }
  printf("%d %d\n", size_x+size_y, nedges);
  for(i = 0; i < size_x; i++) {
    for(j = 0; j < size_y; j++) {
      if(mat[i][j] == 1) {
        printf("%d %d\n", i, size_x+j);
      }
    }
  }
  return 0;
}

int main(int argc, char* argv[])
{
  int size_x;
  int size_y;
  double p;
	struct timeval timev;
	gettimeofday(&timev, NULL);
	srand(timev.tv_sec + timev.tv_usec);

  if(argc != 4) {
    fprintf(stderr, "Three arguments are required\n");
    return 0;
  }
  size_x = atoi(argv[1]);
  size_y = atoi(argv[2]);
  if(size_x + size_y > MAXV) {
    fprintf(stderr, "Too many vertices\n");
    return 0;
  }
  p = atof(argv[3]);
  if(p > 1 || p < 0) {
    fprintf(stderr, "p is not probability\n");
    return 0;
  }
  random_generation(size_x, size_y, p);
  return 0;
}
