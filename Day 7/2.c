#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int datSize = 256;
int MAX_STRING_LEN = 256;
char **Data2d = NULL;
int **visited = NULL;
size_t dataSize = 0;
void printstructure(char **data);
int findSplits(char **data);
int findTimelines(char **data, int **visited, int row, int col);

typedef struct node {
  int vertex[2];
  struct node *next;
} node;

int main(void) {
  FILE *input = fopen("input.txt", "r");
  Data2d = (char **)malloc(datSize * sizeof(char *));
  for (int i = 0; i < datSize; i++) {
    Data2d[i] = (char *)malloc(MAX_STRING_LEN * sizeof(char));
  }
  char line[256];
  while (fgets(line, 256, input) != NULL) {
    strcpy(Data2d[dataSize], line);
    dataSize++;
  }
  visited = (int **)malloc(datSize * sizeof(int *));
  for (int i = 0; i < datSize; i++) {
    visited[i] = (int *)malloc(MAX_STRING_LEN * sizeof(int));
    for (int j = 0; j < MAX_STRING_LEN; j++) {
      visited[i][j] = -1;
    }
  }
  int row = 0;
  int col = dataSize / 2 - 1;
  printf("Number of timelines is %d\n",
         findTimelines(Data2d, visited, row, col));
  for (int i = 0; i < dataSize; i++) {
    free(Data2d[i]);
    free(visited[i]);
  }
  free(Data2d);
  free(visited);
  fclose(input);
  return EXIT_SUCCESS;
}

int findTimelines(char **data, int **visited, int row, int col) {
  int total = 0;
  while (data[row][col] != '^') {
    row += 1;
    if (row == dataSize) {
      return 1;
    }
  }
  if (data[row][col] == '^') {
    total += findTimelines(data, visited, row, col + 1);
    total += findTimelines(data, visited, row, col - 1);
    visited[row][col] = total;
    return total;
  } else {
    return visited[row][col];
  }
}
