#include <stdio.h>
#include <stdlib.h>

#define MAX 10


void inputGraph(int graph[MAX][MAX], int n, int edges) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    // Input the edges from the user
    printf("Enter edges (source, destination):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        printf("Edge %d: ", i + 1);
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }
}


void inputHeuristics(int heuristics[MAX], int n) {
    printf("Enter heuristic values for each node:\n");
    for (int i = 0; i < n; i++) {
        printf("Heuristic value for node %d: ", i);
        scanf("%d", &heuristics[i]);
    }
}


int find_min_heuristic(int open[], int heuristics[], int n) {
    int min_index = -1;
    int min_value = 9999;

    for (int i = 0; i < n; i++) {
        if (open[i] && heuristics[i] < min_value) {
            min_value = heuristics[i];
            min_index = i;
        }
    }
    return min_index;
}

void best_first_search(int graph[MAX][MAX], int heuristics[MAX], int start, int goal, int n) {
    int closed[MAX] = {0};
    int open[MAX] = {0};
    open[start] = 1;

    printf("Path: ");

    while (1) {
        int current = find_min_heuristic(open, heuristics, n);

        if (current == -1) {
            printf("No path found.\n");
            return;
        }

        printf("%d ", current);

        if (current == goal) {
            printf("\nGoal node reached!\n");
            return;
        }

        open[current] = 0;
        closed[current] = 1;


        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !closed[i]) {
                open[i] = 1;
            }
        }
    }
}

int main() {
    int n, edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    int graph[MAX][MAX];
    int heuristics[MAX];

    inputGraph(graph, n, edges);
    inputHeuristics(heuristics, n);

    int start, goal;
    printf("Enter the start node: ");
    scanf("%d", &start);
    printf("Enter the goal node: ");
    scanf("%d", &goal);


    best_first_search(graph, heuristics, start, goal, n);

    return 0;
}
