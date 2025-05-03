#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6  // Number of hiking trail checkpoints

// Function to find the node with the minimum distance value
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Function to print the shortest path using the parent array
void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Function to print the final result
void printSolution(int dist[], int parent[], int src, int dest) {
    printf("\nShortest distance from checkpoint %d to %d: %d units\n", src, dest, dist[dest]);
    printf("Path: ");
    printPath(parent, dest);
    printf("\n");
}

// Dijkstra's Algorithm to find the shortest path and track the path taken
void dijkstra(int graph[V][V], int src, int dest) {
    int dist[V];  
    bool sptSet[V];
    int parent[V]; // Stores the shortest path tree

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1; // Initialize parent of each node as -1 (no parent)
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u; // Track the path
            }
    }

    printSolution(dist, parent, src, dest);
}

// Main function to execute the GPS system
int main() {
    // Example hiking trail map (Graph representation)
    // Weights represent difficulty (higher = more difficult)
    int hikingMap[V][V] = {
        {0, 4, 0, 0, 0, 10}, 
        {4, 0, 2, 5, 0, 0}, 
        {0, 2, 0, 8, 0, 0}, 
        {0, 5, 8, 0, 6, 3}, 
        {0, 0, 0, 6, 0, 7}, 
        {10, 0, 0, 3, 7, 0}
    };

    int start, destination;
    printf("Enter the starting checkpoint (0 to %d): ", V - 1);
    scanf("%d", &start);
    printf("Enter the destination checkpoint (0 to %d): ", V - 1);
    scanf("%d", &destination);

    if (start < 0 || start >= V || destination < 0 || destination >= V) {
        printf("Invalid input! Checkpoints should be between 0 and %d.\n", V - 1);
        return 1;
    }

    printf("\nCalculating shortest route...\n");
    dijkstra(hikingMap, start, destination);

    return 0;
}
