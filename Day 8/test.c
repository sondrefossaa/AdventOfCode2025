#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS 1000

typedef struct {
  int x, y, z;
} Point;

typedef struct {
  int u, v;
  long long dist_sq;
} Edge;

// Union-Find (Disjoint Set Union) data structure
int parent[MAX_POINTS];
int size[MAX_POINTS];

void uf_init(int n) {
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    size[i] = 1;
  }
}

int uf_find(int x) {
  if (parent[x] != x) {
    parent[x] = uf_find(parent[x]); // path compression
  }
  return parent[x];
}

void uf_union(int x, int y) {
  int rootX = uf_find(x);
  int rootY = uf_find(y);

  if (rootX == rootY)
    return;

  // union by size
  if (size[rootX] < size[rootY]) {
    parent[rootX] = rootY;
    size[rootY] += size[rootX];
  } else {
    parent[rootY] = rootX;
    size[rootX] += size[rootY];
  }
}

// Comparison function for qsort - sort edges by distance
int compare_edges(const void *a, const void *b) {
  Edge *edgeA = (Edge *)a;
  Edge *edgeB = (Edge *)b;

  if (edgeA->dist_sq < edgeB->dist_sq)
    return -1;
  if (edgeA->dist_sq > edgeB->dist_sq)
    return 1;
  return 0;
}

// Comparison function for qsort - sort integers in descending order
int compare_desc(const void *a, const void *b) {
  return (*(int *)b - *(int *)a);
}

long long squared_distance(Point *a, Point *b) {
  long long dx = a->x - b->x;
  long long dy = a->y - b->y;
  long long dz = a->z - b->z;
  return dx * dx + dy * dy + dz * dz;
}

int main() {
  FILE *file = fopen("input.txt", "r");
  if (!file) {
    printf("Error opening file\n");
    return 1;
  }

  Point points[MAX_POINTS];
  int point_count = 0;
  char line[256];

  // Read all points
  while (fgets(line, sizeof(line), file) && point_count < MAX_POINTS) {
    Point *p = &points[point_count];
    if (sscanf(line, "%d,%d,%d", &p->x, &p->y, &p->z) == 3) {
      point_count++;
    }
  }
  fclose(file);

  printf("Read %d points\n", point_count);

  // Initialize Union-Find
  uf_init(point_count);

  // Determine how many connections to make
  int connections_to_make;
  if (point_count <= 20) {
    connections_to_make = 10;
    printf("Small example detected, making %d connections\n",
           connections_to_make);
  } else {
    connections_to_make = 1000;
    printf("Full input detected, making %d connections\n", connections_to_make);
  }

  // Create all possible edges
  int edge_count = point_count * (point_count - 1) / 2;
  Edge *edges = (Edge *)malloc(edge_count * sizeof(Edge));

  printf("Generating %d edges...\n", edge_count);

  int edge_idx = 0;
  for (int i = 0; i < point_count; i++) {
    for (int j = i + 1; j < point_count; j++) {
      edges[edge_idx].u = i;
      edges[edge_idx].v = j;
      edges[edge_idx].dist_sq = squared_distance(&points[i], &points[j]);
      edge_idx++;
    }
  }

  // Sort edges by distance (closest first)
  printf("Sorting edges...\n");
  qsort(edges, edge_count, sizeof(Edge), compare_edges);

  // Make connections
  printf("Making connections...\n");
  int connections_made = 0;
  int next_edge = 0;

  while (connections_made < connections_to_make && next_edge < edge_count) {
    Edge e = edges[next_edge];

    // Only connect if they're in different components
    if (uf_find(e.u) != uf_find(e.v)) {
      uf_union(e.u, e.v);
      connections_made++;

      if (connections_made % 100 == 0) {
        printf("  Made %d connections\n", connections_made);
      }
    }
    next_edge++;
  }

  printf("Total connections made: %d\n", connections_made);

  // Count component sizes
  int *component_sizes = (int *)malloc(point_count * sizeof(int));
  bool *visited = (bool *)calloc(point_count, sizeof(bool));
  int component_count = 0;

  for (int i = 0; i < point_count; i++) {
    int root = uf_find(i);
    if (!visited[root]) {
      visited[root] = true;
      component_sizes[component_count++] = size[root];
    }
  }

  // Sort component sizes in descending order
  qsort(component_sizes, component_count, sizeof(int), compare_desc);

  printf("\nComponent sizes (largest first):\n");
  for (int i = 0; i < component_count && i < 10; i++) {
    printf("  %d: size %d\n", i + 1, component_sizes[i]);
  }

  // Calculate product of three largest components
  long long product = 1;
  for (int i = 0; i < 3 && i < component_count; i++) {
    product *= component_sizes[i];
  }

  printf("\nProduct of three largest components: %lld\n", product);

  // Clean up
  free(edges);
  free(component_sizes);
  free(visited);

  return 0;
}
