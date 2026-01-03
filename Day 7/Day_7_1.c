#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int datSize = 256;
int MAX_STRING_LEN = 256;
char **Data2d = NULL;
size_t dataSize = 0;
void printstructure(char **data);
int findSplits(char **data);
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
  // printstructure(Data2d);
  for (int i = 0; i < dataSize; i++) {
    free(Data2d[i]);
  }
  free(Data2d);
  fclose(input);
  return EXIT_SUCCESS;
}

int findSplits(char **data) {
  int splits = 0;
  for (int i = 2; i < dataSize; i++) {
    for (int j = 0; j < strlen(data[i]); j++) {
      if (data[i - 1][j] == '|' && data[i][j] == '^') {
        splits += 1;

        // Split line
        for (int a = -1; a < 2; a += 2) {
          if (a + j <= dataSize && data[i + 1][j + a] != '|') {
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
