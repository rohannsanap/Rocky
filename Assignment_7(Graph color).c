#include <stdio.h>
#include <stdbool.h>

#define MAX 100

void graphColoring(int graph[MAX][MAX], int n) {
    int result[MAX];
    result[0] = 0;
    for (int i = 1; i < n; i++)
        result[i] = -1;

    bool available[MAX];
    for (int i = 0; i < n; i++)
        available[i] = false;

    for (int u = 1; u < n; u++) {
        for (int i = 0; i < n; i++) {
            if (graph[u][i] && result[i] != -1)
                available[result[i]] = true;
        }

        int color;
        for (color = 0; color < n; color++) {
            if (!available[color])
                break;
        }

        result[u] = color;

        for (int i = 0; i < n; i++)
            available[i] = false;
    }

    printf("Vertex   Color\n");
    for (int u = 0; u < n; u++)
        printf("   %d        %d\n", u, result[u]);
}

int main() {
    int n;
    int graph[MAX][MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    graphColoring(graph, n);

    return 0;
}
