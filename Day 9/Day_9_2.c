#include <inttypes.h>
#include <iso646.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 500
int data_size = 0;
typedef struct position {
  int x, y;
} position;

int *seenYpos = NULL;

position *positions[MAX_LEN];
position *positions_sorted_x[MAX_LEN];
position *positions_sorted_y[MAX_LEN];
char *filepath = "input.txt";

long getArea(position first, position second) {
  int64_t width = llabs(first.x - second.x) + 1;
  int64_t height = llabs(first.y - second.y) + 1;
  return width * height;
}
int compare_x(const void *a, const void *b) {
  position *p1 = *(position **)a;
  position *p2 = *(position **)b;
  return p1->x - p2->x;
}

int compare_y(const void *a, const void *b) {
  position *p1 = *(position **)a;
  position *p2 = *(position **)b;
  return p1->y - p2->y;
}
int findIndex(int value, position **posArr, bool search_x) {
  int left = 0;
  int right = data_size - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    int mid_value = search_x ? posArr[mid]->x : posArr[mid]->y;
    if (mid_value == value) {
      return mid;
    } else if (mid_value < value) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return left;
}

bool checkGreen(position p1, position p2) {
  // check the y dir of the first point
  position new = {p1.x + 1, p1.y + 1};
  bool fTest = false;
  for (int i = 0; i < data_size; i++) {
    if (positions[i]->x == p1.x and positions[i]->y == p2.y) {
      fTest = true;
      break;
    }
  }
  if (!fTest) {
    return false;
  }
  // Raycast
  // For each x pos thats bigger than p1 x check if it has a point with same x
  // and bigger or same y as p2.y
  if (seenYpos == NULL) {
    seenYpos = (int *)calloc(data_size, sizeof(int));
  } else {
    memset(seenYpos, 0, data_size * sizeof(int));
  }

  int rayCastCol = 0;
  for (int i = 0; i < data_size; i++) {
    if (positions[i]->x > p1.x) {
      bool foundAbove = false;
      for (int j = 0; j < data_size; j++) {
        if (positions[j]->y >= p2.y and positions[j]->x == positions[i]->x) {
          if (!seenYpos[j]) {
            seenYpos[j] = 1;
            foundAbove = true;
          }
        }
      }
      if (foundAbove) {
        rayCastCol++;
      }
    }
  }
  return rayCastCol % 2 == 0;
}
int64_t getBiggestArea() {
  int64_t biggest_area = 0;
  for (int i = 0; i < data_size; i++) {
    for (int j = 0; j < data_size; j++) {
      int64_t area = getArea(*positions[i], *positions[j]);
      if (area > biggest_area and checkGreen(*positions[i], *positions[j])) {
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
  // Create sorted arrays
  for (int i = 0; i < data_size; i++) {
    positions_sorted_x[i] = positions[i];
    positions_sorted_y[i] = positions[i];
  }
  qsort(positions_sorted_x, data_size, sizeof(position *), compare_x);
  qsort(positions_sorted_y, data_size, sizeof(position *), compare_y);
  int64_t result = getBiggestArea();
  printf("Biggest area between red tiles: %" PRId64 "\n", result);

  // Cleanup
  if (seenYpos != NULL) {
    free(seenYpos);
  }
  for (int i = 0; i < data_size; i++) {
    free(positions[i]);
  }

  return 0;
}
