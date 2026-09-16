# Distance Vector Algorithm Simulator

## Overview

The **Distance Vector algorithm** is used to calculate the least-cost path between nodes in a weighted graph.

Unlike [Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm), which assumes that each node has complete knowledge of the graph topology, the Distance Vector algorithm works with a more limited view.

Each node only knows:

* The cost of links to its immediate neighbours
* The distance information received from neighbouring nodes

Nodes then exchange information iteratively to improve their understanding of the least-cost paths to all destinations.

## Initial Distance Vector

For a node \(x\), the initial distance to another node \(y\) can be represented as:

$$
D_x(y) =
\begin{cases}
0 & \text{if } x = y \\
c(x,y) & \text{if } x \text{ and } y \text{ are immediate neighbours} \\
\infty & \text{otherwise}
\end{cases}
$$

Where:

* \(D_x(y)\) = distance from node \(x\) to destination \(y\)
* \(c(x,y)\) = direct link cost between \(x\) and \(y\)
* \(\infty\) = destination is initially unreachable

## How It Works

When a node discovers a better route to a destination, it updates its own distance vector and notifies its neighbours.

This process continues iteratively until the network reaches **convergence**.

### Convergence

Convergence is the state where no further distance-vector updates are required because all nodes have learned the current least-cost paths.

Because the algorithm is decentralised, convergence can be slower than algorithms that assume complete knowledge of the network topology.

## Good News Travels Fast, Bad News Travels Slow

The Distance Vector algorithm has an important characteristic:

> **Good news travels fast, bad news travels slow.**

When a shorter route is discovered, the improvement can propagate quickly through neighbouring nodes.

However, when a link fails or its cost increases, the change may propagate more slowly because nodes do not immediately have complete knowledge of the network.

## Count-to-Infinity Problem

A consequence of the asynchronous nature of Distance Vector routing is the **count-to-infinity problem**.

This can occur when a link fails and neighbouring nodes have outdated information about routes to a destination.

Nodes may repeatedly increase their estimated cost to the destination without correctly recognising that the destination is unreachable.

This can cause:

* Repeated distance-vector updates
* Increasing route costs
* Slow convergence
* Network instability

More information about this problem can be found in [Route Poisoning and Count to Infinity Problem](https://www.geeksforgeeks.org/route-poisoning-and-count-to-infinity-problem-in-routing/).

## Key Points

* Distance Vector is a **decentralised routing algorithm**.
* Each node initially knows only its own distance and the costs to its neighbours.
* Nodes exchange distance-vector information with their neighbours.
* Better routes cause distance vectors to be updated.
* The process continues until the network converges.
* Link failures can take longer to propagate.
* The **count-to-infinity problem** is a known issue with Distance Vector routing.

## Source

[Distance Vector Algorithm Simulator](https://distance-vector-algorithm-simulator.onrender.com/tables)

[Dijkstra's Algorithm — Wikipedia](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

[Count-to-Infinity Problem — GeeksforGeeks](https://www.geeksforgeeks.org/computer-networks/route-poisoning-and-count-to-infinity-problem-in-routing/)