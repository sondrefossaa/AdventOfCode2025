#include <inttypes.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 500
int data_size = 0;
typedef struct position {
  int x, y;
} position;
position *positions[MAX_LEN];

char *filepath = "input.txt";

long getArea(position first, position second) {
  int64_t width = llabs(first.x - second.x) + 1;

  int64_t height = llabs(first.y - second.y) + 1;
  return width * height;
}
int64_t getBiggestArea() {
  int64_t biggest_area = 0;
  for (int i = 0; i < data_size; i++) {
    for (int j = 0; j < data_size; j++) {
      int64_t area = getArea(*positions[i], *positions[j]);
      if (area > biggest_area) {
        biggest_area = area;
      }
    }
  }
  return biggest_area;
}
int main(void) {

  FILE *input = fopen(filepath, "r");
  char buffer[256];
  while (fgets(buffer, 256, input) != NULL) {
    positions[data_size] = malloc(sizeof(position));
    int fieldCount = 0;
    char *token = strtok(buffer, ",");
    while (token != NULL) {
      token[strcspn(token, "\n")] = '\0';
      switch (fieldCount) {
      case 0:
        positions[data_size]->x = atoi(token);
        break;
      case 1:
        positions[data_size]->y = atoi(token);
        break;
      }
      fieldCount++;
      token = strtok(NULL, ",\n");
    }
    data_size += 1;
  }
  fclose(input);
  

  
  // for (int i = 0; i < data_size; i++) {
  //   printf("[%d, %d]", positions[i]->x, positions[i]->y);
  // }
  // printf("%d", data_size);
  int64_t result = getBiggestArea();
  printf("Biggest area between red tiles: %" PRId64 "\n", result);
  return 1;
}
