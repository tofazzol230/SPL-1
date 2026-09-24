# Bellman-Ford and Dijkstra Algorithms

This note introduces the two shortest-path algorithms planned for the SPL-1 Distance Vector Routing Simulator.

## Bellman-Ford

Bellman-Ford finds shortest paths from one starting node. In a Distance Vector network, each router repeatedly uses information from its immediate neighbors to improve its routes.

For router **X** and destination **D**:

> New cost from X to D through neighbor N = cost from X to N + N's advertised cost to D

X keeps the cheapest option it knows. Routers repeat these updates until no route changes.

### C++ example

This example runs Bellman-Ford on a graph. It works with negative edge weights, but the routing simulator should use nonnegative link costs.

```cpp
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Edge {
    int from;
    int to;
    int cost;
};

int main() {
    const int routerCount = 4;
    const int INF = numeric_limits<int>::max() / 4;

    // Routers: A=0, B=1, C=2, D=3
    vector<Edge> links = {
        {0, 1, 2},  // A-B costs 2
        {0, 2, 5},  // A-C costs 5
        {1, 2, 1},  // B-C costs 1
        {2, 3, 3}   // C-D costs 3
    };

    int source = 0; // Start at router A
    vector<int> distance(routerCount, INF);
    distance[source] = 0;

    // Relax every edge up to routerCount - 1 times.
    for (int round = 1; round < routerCount; ++round) {
        bool changed = false;

        for (const Edge& edge : links) {
            if (distance[edge.from] != INF &&
                distance[edge.from] + edge.cost < distance[edge.to]) {
                distance[edge.to] = distance[edge.from] + edge.cost;
                changed = true;
            }

            // For an undirected network link, also check the reverse direction.
            if (distance[edge.to] != INF &&
                distance[edge.to] + edge.cost < distance[edge.from]) {
                distance[edge.from] = distance[edge.to] + edge.cost;
                changed = true;
            }
        }

        if (!changed) {
            break; // No routes changed, so the result has stabilized.
        }
    }

    cout << "Shortest costs from router A:\\n";
    for (int router = 0; router < routerCount; ++router) {
        cout << char('A' + router) << ": ";

        if (distance[router] == INF) {
            cout << "unreachable\\n";
        } else {
            cout << distance[router] << '\\n';
        }
    }
}
```

This finds costs from one source. A Distance Vector simulator will need each router to maintain its own table and exchange information with its neighbors in rounds.

## Dijkstra's algorithm

Dijkstra also finds shortest paths from one starting node, but it repeatedly selects the unvisited router with the smallest known cost. It then checks whether traveling through that router improves routes to its neighbors.

Dijkstra requires **nonnegative edge costs**.

### C++ example

This uses a priority queue to find the next closest router efficiently.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int to;
    int cost;
};

int main() {
    const int routerCount = 4;
    const int INF = numeric_limits<int>::max() / 4;

    // Routers: A=0, B=1, C=2, D=3
    vector<vector<Edge>> network(routerCount);

    auto addLink = [&](int a, int b, int cost) {
        network[a].push_back({b, cost});
        network[b].push_back({a, cost}); // Links work both ways
    };

    addLink(0, 1, 2); // A-B
    addLink(0, 2, 5); // A-C
    addLink(1, 2, 1); // B-C
    addLink(2, 3, 3); // C-D

    int source = 0; // Start at router A
    vector<int> distance(routerCount, INF);
    distance[source] = 0;

    // Each item is (cost so far, router).
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > nextRouters;

    nextRouters.push({0, source});

    while (!nextRouters.empty()) {
        auto [costSoFar, current] = nextRouters.top();
        nextRouters.pop();

        // Ignore an old queue entry if a cheaper route was found later.
        if (costSoFar != distance[current]) {
            continue;
        }

        for (const Edge& edge : network[current]) {
            int newCost = costSoFar + edge.cost;

            if (newCost < distance[edge.to]) {
                distance[edge.to] = newCost;
                nextRouters.push({newCost, edge.to});
            }
        }
    }

    cout << "Shortest costs from router A:\\n";
    for (int router = 0; router < routerCount; ++router) {
        cout << char('A' + router) << ": ";

        if (distance[router] == INF) {
            cout << "unreachable\\n";
        } else {
            cout << distance[router] << '\\n';
        }
    }
}
```

## Key difference

| Bellman-Ford | Dijkstra |
|---|---|
| Improves routes by repeatedly checking edges or exchanging neighbor information | Expands outward from the closest known router |
| Can handle negative edge weights in general graph problems | Requires nonnegative edge weights |
| A good fit for demonstrating Distance Vector routing | A good fit for Link State routing |
| Naturally shows routes changing over rounds | Usually calculates routes from a full view of the network |

For this SPL-1 project, **Bellman-Ford / Distance Vector is the main algorithm to build first**. Dijkstra is useful later as a comparison mode. Both examples above use a single starting router; the simulator's Distance Vector implementation will model every router's routing table and update it over rounds.
