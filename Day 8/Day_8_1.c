#include <iso646.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATA_LEN 20

typedef struct pos {
  int x;
  int y;
  int z;
  bool handled;
} pos;

typedef struct jbox {
  int index;
  struct jbox *next;
} jbox;
typedef struct circuit {
  int children_count;
  jbox *boxes;
} circuit;

circuit *circuits[DATA_LEN] = {NULL};
int circuit_count = 0;
pos **posArr = NULL;

double findEuclidianDistance(int x, int y, int z) {
  return sqrt(x * x + y * y + z * z);
}

void insertIntoCircuit(int cloest_idx, int idx) {

  // Check if indexes already in the circuits
  for (int i = 0; i < circuit_count; i++) {
    circuit *head = circuits[i];
    jbox *current = circuits[i]->boxes;
    while (current != NULL) {
      if (current->index == idx) {
        // Make new node for cloest_idx
        jbox *new_jbox = malloc(sizeof(jbox));
        new_jbox->index = cloest_idx;
        new_jbox->next = head->boxes;
        head->boxes = new_jbox;
        head->children_count += 1;
        return;
      } else if (current->index == cloest_idx) {
        printf("a\n");

        // Make new node for idx
        jbox *new_jbox = malloc(sizeof(jbox));
        new_jbox->index = idx;
        new_jbox->next = head->boxes;
        head->boxes = new_jbox;
        head->children_count += 1;
        return;
      }
      current = current->next;
    }
  }
  // Make new entry if indexes not in table
  jbox *closest_jbox = malloc(sizeof(jbox));
  closest_jbox->index = cloest_idx;
  closest_jbox->next = NULL;
  jbox *idx_jbox = malloc(sizeof(jbox));
  idx_jbox->index = idx;
  idx_jbox->next = closest_jbox;
  circuit *start_circuit = malloc(sizeof(circuit));
  start_circuit->children_count = 2;
  start_circuit->boxes = idx_jbox;
  circuits[circuit_count] = start_circuit;
  circuit_count++;
  return;
}
void printCircuits() {
  for (int i = 0; i < circuit_count; i++) {
    jbox *current = circuits[i]->boxes;
    while (current != NULL) {
      printf("Jbox with index %d and position(%d,%d,%d) is in circuit %d which "
             "has a length of %d \n",
             current->index, posArr[current->index]->x,
             posArr[current->index]->y, posArr[current->index]->z, i,
             circuits[i]->children_count);
      current = current->next;
    }
  }
}

// Does not, work, has to find the one with smalles uclidian distance.
void fillCircuitsRecursive() {
  static int connections = 0;
  double min_distance = INFINITY;
  int closest_idx = -1;
  int origin_idx = -1;

  // Find closest pair among unhandled points
  for (int i = 0; i < DATA_LEN; i++) {
    if (posArr[i]->handled)
      continue;

    for (int j = 0; j < DATA_LEN; j++) {
      if (j == i || posArr[j]->handled)
        continue;

      double dist = findEuclidianDistance(posArr[j]->x - posArr[i]->x,
                                          posArr[j]->y - posArr[i]->y,
                                          posArr[j]->z - posArr[i]->z);

      if (dist < min_distance) {
        min_distance = dist;
        closest_idx = j;
        origin_idx = i;
      }
    }
  }

  if (origin_idx == -1 || closest_idx == -1) {
    return;
  }

  // Process current smallest pair
  connections += 1;
  if (connections == 10) {
    return;
  }
  insertIntoCircuit(closest_idx, origin_idx);
  printf("%d, %d (dist: %.2f)\n", origin_idx, closest_idx, min_distance);

  posArr[origin_idx]->handled = true;

  fillCircuitsRecursive();
}

// Bubble sort
void sortCircuits() {
  int swapped;
  for (int i = 0; i < circuit_count - 1; i++) {
    swapped = 0;
    for (int j = 0; j < circuit_count - i - 1; j++) {
      if (circuits[j]->children_count > circuits[j + 1]->children_count) {
        circuit *temp = circuits[j];
        circuits[j] = circuits[j + 1];
        circuits[j + 1] = temp;
        swapped = 1;
      }
    }
    // If no swaps happened, array is sorted
    if (!swapped)
      break;
  }
}
int multThreeBiggest() {
  sortCircuits();
  return 1;
}
int main() {
  // init table
  for (int i = 0; i < DATA_LEN; i++) {
    circuits[i] = NULL;
  }

  FILE *input = fopen("input2.txt", "r");
  char buffer[256];
  // Define 3d default array
  posArr = (pos **)malloc(sizeof(pos *) * DATA_LEN);
  int i = 0;
  while (fgets(buffer, 256, input) != NULL) {
    posArr[i] = (pos *)(malloc(sizeof(pos)));

    int fieldCount = 0;
    char *token = strtok(buffer, ",");
    while (token != NULL) {
      token[strcspn(token, "\n")] = '\0';
      switch (fieldCount) {
      case 0:
        posArr[i]->x = atoi(token);
      case 1:
        posArr[i]->y = atoi(token);
      case 2:
        posArr[i]->z = atoi(token);
      }
      fieldCount++;
      token = strtok(NULL, ",\n");
    }
    i += 1;
  }
  fillCircuitsRecursive();
  printf("Answer: %d\n", multThreeBiggest());
  printCircuits();
  fclose(input);
  // Print results
  // printf("Loaded %d positions:\n", i);
  // for (int j = 0; j < i; j++) {
  //   printf("  [%d] x=%d, y=%d, z=%d\n", j, posArr[j]->x, posArr[j]->y,
  //          posArr[j]->z);
  // }

  // Cleanup
  for (int j = 0; j < i; j++) {
    free(posArr[j]);
  }
  for (int i = 0; i < circuit_count; i++) {
    jbox *current = circuits[i]->boxes;
    while (current != NULL) {
      jbox *prev = current;
      current = current->next;
      free(prev);
    }
    circuits[i] = NULL;
  }

  return EXIT_SUCCESS;
}
