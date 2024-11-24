 #include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 9999

struct Node {
    int vertex;
    int g;
    int h;
    int f;
    struct Node* next;
};

struct Graph {
    int numVertices;
    int adjMatrix[MAX][MAX];
    int heuristic[MAX];
};

struct Node* createNode(int vertex, int g, int h) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->g = g;
    newNode->h = h;
    newNode->f = g + h;
    newNode->next = NULL;
    return newNode;
}

struct PriorityQueue {
    struct Node* head;
};

struct PriorityQueue* createPriorityQueue() {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->head = NULL;
    return pq;
}

void enqueue(struct PriorityQueue* pq, struct Node* newNode) {
    if (pq->head == NULL || pq->head->f > newNode->f) {
        newNode->next = pq->head;
        pq->head = newNode;
    } else {
        struct Node* temp = pq->head;
        while (temp->next != NULL && temp->next->f <= newNode->f) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

struct Node* dequeue(struct PriorityQueue* pq) {
    if (pq->head == NULL)
        return NULL;
    struct Node* temp = pq->head;
    pq->head = pq->head->next;
    return temp;
}

int isEmpty(struct PriorityQueue* pq) {
    return pq->head == NULL;
}

void aStarSearch(struct Graph* graph, int start, int goal) {
    int visited[MAX] = {0};
    struct PriorityQueue* pq = createPriorityQueue();

    struct Node* startNode = createNode(start, 0, graph->heuristic[start]);
    enqueue(pq, startNode);

    printf("A* Search traversal: \n");

    while (!isEmpty(pq)) {
        struct Node* currentNode = dequeue(pq);
        int currentVertex = currentNode->vertex;

        if (visited[currentVertex]) {
            continue;
        }

        printf("%d ", currentVertex);
        visited[currentVertex] = 1;

        if (currentVertex == goal) {
            printf("\nGoal node %d found!\n", goal);
            return;
        }

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] != 0 && !visited[i]) {
                int g = currentNode->g + graph->adjMatrix[currentVertex][i];
                int h = graph->heuristic[i];
                struct Node* newNode = createNode(i, g, h);
                enqueue(pq, newNode);
            }
        }
    }

    printf("\nGoal node not reachable!\n");
}

int main() {
    int n, edges, u, v, weight, start, goal;

    struct Graph graph;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    graph.numVertices = n;

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph.adjMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (source, destination, weight): ");
        scanf("%d %d %d", &u, &v, &weight);
        graph.adjMatrix[u][v] = weight;
        graph.adjMatrix[v][u] = weight;
    }

    printf("Enter heuristic values for each vertex:\n");
    for (int i = 0; i < n; i++) {
        printf("Heuristic for vertex %d: ", i);
        scanf("%d", &graph.heuristic[i]);
    }

    printf("Enter the start vertex: ");
    scanf("%d", &start);

    printf("Enter the goal vertex: ");
    scanf("%d", &goal);

    aStarSearch(&graph, start, goal);

    return 0;
}
