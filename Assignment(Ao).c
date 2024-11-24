#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 9999

struct Node {
    int id;
    int heuristic;
    int isSolved;
    int isAndNode;
    struct Node* successors[MAX];
    int numSuccessors;
    int cost[MAX];
};

struct Node* createNode(int id, int heuristic, int isAndNode) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = id;
    newNode->heuristic = heuristic;
    newNode->isSolved = 0;
    newNode->isAndNode = isAndNode;
    newNode->numSuccessors = 0;
    return newNode;
}

void addSuccessor(struct Node* parent, struct Node* child, int cost) {
    parent->successors[parent->numSuccessors] = child;
    parent->cost[parent->numSuccessors] = cost;
    parent->numSuccessors++;
}

int minCostIndex(struct Node* node) {
    int minCost = INF;
    int minIndex = -1;
    for (int i = 0; i < node->numSuccessors; i++) {
        int totalCost = node->cost[i] + node->successors[i]->heuristic;
        if (totalCost < minCost) {
            minCost = totalCost;
            minIndex = i;
        }
    }
    return minIndex;
}

void aoStar(struct Node* node) {
    if (node->isSolved || node->numSuccessors == 0) {
        return;
    }

    int bestIndex = minCostIndex(node);

    if (node->isAndNode) {
        for (int i = 0; i < node->numSuccessors; i++) {
            aoStar(node->successors[i]);
        }
        int totalCost = 0;
        for (int i = 0; i < node->numSuccessors; i++) {
            totalCost += node->cost[i] + node->successors[i]->heuristic;
        }
        node->heuristic = totalCost;
    } else {
        aoStar(node->successors[bestIndex]);
        node->heuristic = node->cost[bestIndex] + node->successors[bestIndex]->heuristic;
    }

    int isAllSolved = 1;
    for (int i = 0; i < node->numSuccessors; i++) {
        if (!node->successors[i]->isSolved) {
            isAllSolved = 0;
            break;
        }
    }

    if (isAllSolved) {
        node->isSolved = 1;
        printf("Node %d is solved!\n", node->id);
    }
}

int main() {
    int numNodes, id, heuristic, isAndNode, parentId, childId, cost, numSuccessors;
    struct Node* nodes[MAX];

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    for (int i = 0; i < numNodes; i++) {
        printf("Enter node id, heuristic value, and isAndNode (0 for OR, 1 for AND): ");
        scanf("%d %d %d", &id, &heuristic, &isAndNode);
        nodes[id] = createNode(id, heuristic, isAndNode);
    }

    printf("Enter the successors (parent, child, cost) for each node:\n");
    for (int i = 0; i < numNodes; i++) {
        printf("Enter the parent node id: ");
        scanf("%d", &parentId);
        printf("Enter the number of successors for node %d: ", parentId);
        scanf("%d", &numSuccessors);

        for (int j = 0; j < numSuccessors; j++) {
            printf("Enter child node id and cost: ");
            scanf("%d %d", &childId, &cost);
            addSuccessor(nodes[parentId], nodes[childId], cost);
        }
    }

    int startNode;
    printf("Enter the start node: ");
    scanf("%d", &startNode);

    aoStar(nodes[startNode]);

    return 0;
}
