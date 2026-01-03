#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int datSize = 256;
int MAX_STRING_LEN = 256;
char **Data2d = NULL;
size_t dataSize = 0;
void printstructure(char **data);
int findSplits(char **data);
int findTimelines(char **data);

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
    // printf("%s", line);
    strcpy(Data2d[dataSize], line);
    dataSize++;
  }

  printf("Number of splits is %d \n", findSplits(Data2d));
  printf("Number of timelines is %d\n", findTimelines(Data2d));
  // printstructure(Data2d);
  for (int i = 0; i < dataSize; i++) {
    free(Data2d[i]);
  }
  free(Data2d);
  fclose(input);
  return EXIT_SUCCESS;
}

int findTimelines(char **data) {
  bool **visited = malloc(dataSize * sizeof(bool *));
  for (int i = 0; i < dataSize; i++) {
    visited[i] = malloc(sizeof(bool) * strlen(data[i]));
  }
  node *head = (node *)malloc(sizeof(node));
  head->vertex[0] = 1;
  head->vertex[1] = strlen(data[1]) / 2 - 1;
  head->next = NULL;
  node *stack = head;
  int pathCount = 0;
  // Expand head
  while (stack != NULL) {
    // Find children
    node *current = stack;
    stack = stack->next;
    int i = current->vertex[0];
    int j = current->vertex[1];
    if (i >= dataSize || j >= strlen(data[i]) || visited[i][j]) {
      free(current);
      continue;
    }
    visited[i][j] = true;
    if (data[i][j] == '|') {
      // add next node to stack.
      node *downNode = malloc(sizeof(node));
      downNode->vertex[0] = i + 1;
      downNode->vertex[1] = j;
      downNode->next = stack; // Push onto stack
      stack = downNode;
    } else if (data[i][j] == '^') {
      // Add both nodes after split to stack
      node *rightNode = malloc(sizeof(node));
      rightNode->vertex[0] = i + 1;
      rightNode->vertex[1] = j + 1;
      rightNode->next = stack;
      stack = rightNode;

      node *leftNode = malloc(sizeof(node));
      leftNode->vertex[0] = i + 1;
      leftNode->vertex[1] = j - 1;
      leftNode->next = stack;
      stack = leftNode;
    }
    if (i == dataSize - 1) {
      pathCount += 1;
    }
    free(current);
  }
  for (int i = 0; i < dataSize; i++) {
    free(visited[i]);
  }
  free(visited);
  return pathCount;
}

int findSplits(char **data) {
  int splits = 0;
  for (int i = 2; i < dataSize; i++) {
    for (int j = 0; j < strlen(data[i]); j++) {
      if (data[i - 1][j] == '|' && data[i][j] == '^') {
        splits += 1;

        // Split line
        for (int a = -1; a < 2; a += 2) {
          if (j + a >= 0 && j + a < strlen(data[i + 1]) &&
              data[i + 1][j + a] != '|') {
            data[i + 1][j + a] = '|';
          }
        }
        // printf("%s", data[i]);
      } else if (data[i - 1][j] == '|') {
        // Keep beams persisent
        data[i][j] = '|';
      }
    }
  }
  return splits;
}
void printstructure(char **data) {
  int i = 0;
  for (int i = 0; i < dataSize; i++) {
    printf("%s\n", data[i]);
  }
}
