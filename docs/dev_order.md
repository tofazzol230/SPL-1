## Overall Architecture

```text
                         USER
                          │
                          ▼
                 ┌─────────────────┐
                 │   Java Swing    │
                 │      GUI        │
                 └────────┬────────┘
                          │
                     JSON / IPC
                          │
                          ▼
                 ┌─────────────────┐
                 │   C++ Backend   │
                 │                 │
                 │ Distance Vector │
                 │ Bellman-Ford    │
                 │ Event Engine    │
                 └────────┬────────┘
                          │
                          ▼
                 ┌─────────────────┐
                 │ Simulation State│
                 │                 │
                 │ Routers         │
                 │ Links            │
                 │ Routing Tables  │
                 │ Messages        │
                 └─────────────────┘
```

# Development Flow

### Phase 1 — Project Foundation

First, we create the project structure:

```text
distance-vector-simulator/
│
├── backend/                         # C++ simulation and routing core
│   ├── src/
│   └── Makefile
│
├── gui/                             # Java Swing GUI
│   └── src/
├── tests/                           # Automated and integration tests
│   ├── unit/
│   ├── integration/
│   └── test_cases/
│
├── examples/                        # Sample topologies and scenarios
│   ├── basic/
│   ├── loop/
│   ├── count-to-infinity/
│   ├── failure/
│   └── link-state/
│
├── docs/                            # Project documentation
│   ├── project-overview.md
│   ├── algorithm.md
│   ├── design.md
│   └── experiments.md
│
├── learning/                        # Learning and reference notes
│   ├── git.md
│   ├── networking.md
│   ├── distance-vector.md
│   └── cpp.md
│
├── README.md
├── Makefile
└── .gitignore

```

We will not start with the GUI. First, we build and test the backend.

---

### Phase 2 — C++ Core

First target: a **pure C++ simulator without GUI**.

Main components:

```text
Router
Link
Network
RoutingTable
DistanceVector
```

Then implement the basic Bellman-Ford calculation:

```text
Network
   ↓
Initial Routing Tables
   ↓
Exchange Distance Vectors
   ↓
Bellman-Ford Calculation
   ↓
Update Routing Tables
   ↓
Generate Events
   ↓
Check Convergence
```

No graph library or routing library will be used.

---

### Phase 3 — Discrete-Event Engine

The simulator needs an event system.

Possible events:

```text
Event
├── PERIODIC_UPDATE
├── TRIGGERED_UPDATE
├── LINK_FAILURE
├── LINK_RESTORE
├── LINK_COST_CHANGE
└── MESSAGE_DELIVERY
```

For example:

```text
Round 1
A → B : Distance Vector

Round 2
B → A : Updated Vector
B → C : Updated Vector

Round 3
Routing tables updated

Round 4
No further changes

→ CONVERGED
```

---

### Phase 4 — Routing Problems

Then we implement and demonstrate:

* Routing loops
* Link failure
* Count-to-infinity
* Slow convergence
* Network changes

These are important because they demonstrate the actual behavior of Distance Vector routing.

---

### Phase 5 — Distance Vector Modes

The simulator will support different routing modes:

```text
1. Basic Distance Vector
2. Split Horizon
3. Poison Reverse
4. Hold-Down
5. Configurable Infinity
```

The same topology can be tested using different modes.

---

### Phase 6 — Link State Routing

After the Distance Vector implementation is stable, we add:

```text
Link State Routing
        ↓
Dijkstra's Algorithm
```

So the simulator can provide:

```text
Routing Mode
├── Basic Distance Vector
├── Split Horizon
├── Poison Reverse
├── Hold-Down
└── Link State / Dijkstra
```

---

### Phase 7 — Java Swing GUI

Only after the C++ backend is working correctly, we build the Java Swing interface.

The GUI should eventually contain:

```text
┌──────────────────────────────────────────────┐
│ Distance Vector Routing Simulator            │
├──────────────────────────────────────────────┤
│                                              │
│       A -------- B                           │
│       |          |                           │
│       |          |                           │
│       C -------- D                           │
│                                              │
├──────────────────────────────────────────────┤
│ Mode: [Basic Distance Vector ▼]              │
│                                              │
│ ▶ Start   ⏸ Pause   ⟳ Reset   ⏭ Step        │
│ Speed: ─────────●────                        │
├──────────────────────────────────────────────┤
│ Routing Table                                │
│                                              │
│ Destination | Cost | Next Hop                │
│ B           | 1    | B                       │
│ C           | 2    | B                       │
├──────────────────────────────────────────────┤
│ Event / Message Log                          │
│ A → B : Distance Vector Update               │
│ B updated route to C                         │
│ Network converged                            │
└──────────────────────────────────────────────┘
```

The GUI will allow users to:

* Add routers
* Remove routers
* Add links
* Remove links
* Set link costs
* Change link costs
* Start simulation
* Pause simulation
* Reset simulation
* Step through rounds
* Control simulation speed
* View routing tables
* View events/messages
* View convergence status

---

### Phase 8 — C++ ↔ Java Communication

We then connect the Java GUI with the C++ backend using **JSON/IPC**.

For example, Java could send:

```json
{
  "event": "add_link",
  "from": "A",
  "to": "B",
  "cost": 4
}
```

The C++ backend could return:

```json
{
  "event": "routing_update",
  "router": "A",
  "destination": "C",
  "cost": 6,
  "nextHop": "B"
}
```

This keeps the GUI and routing engine separated.

---

### Phase 9 — Visualization and Animation

After communication works, we add the visual layer.

For example:

```text
A ───────────────► B
       DV Update
```

The GUI can animate routing messages moving between routers while routing tables update dynamically.

We can also visualize:

* Router changes
* Link failures
* Link restoration
* Routing-table changes
* Message activity
* Convergence
* Routing loops

---

### Phase 10 — Testing

We will create test scenarios such as:

```text
tests/
├── basic_dv
├── split_horizon
├── poison_reverse
├── count_to_infinity
├── link_failure
├── link_restore
├── convergence
└── dijkstra
```

Each feature should be tested independently before integrating everything into the GUI.

---

### Phase 11 — Documentation

Finally, update:

```text
README.md
docs/
learning/
```

Documentation should include:

* Project overview
* Architecture
* How to compile
* How to run
* Distance Vector explanation
* Bellman-Ford explanation
* Dijkstra explanation
* Simulation modes
* JSON/IPC design
* Example scenarios
* Screenshots
* Limitations

---

### Phase 12 — Optional Packaging

If time permits and your supervisor approves:

```text
Java JDK
    ↓
jpackage
    ↓
Standalone Desktop Application
```

This will make the simulator easier to demonstrate without manually running all components.

# Final Development Sequence

The actual order will be:

```text
1. Project Structure
        ↓
2. C++ Router & Link
        ↓
3. C++ Network
        ↓
4. Routing Table
        ↓
5. Bellman-Ford
        ↓
6. Distance Vector Exchange
        ↓
7. Convergence Detection
        ↓
8. Discrete-Event Engine
        ↓
9. Link Failure / Restoration
        ↓
10. Count-to-Infinity
        ↓
11. Split Horizon
        ↓
12. Poison Reverse
        ↓
13. Hold-Down / Configurable Infinity
        ↓
14. Dijkstra / Link State
        ↓
15. JSON / IPC
        ↓
16. Java Swing GUI
        ↓
17. Visualization & Animation
        ↓
18. Testing
        ↓
19. Documentation
        ↓
20. Optional jpackage
```

**The key principle:** we should **not start by building the GUI**. We first make the C++ routing engine correct, test it thoroughly, and then build the Java GUI around that stable backend.

So our **first actual coding milestone** should be:

> **Build the C++ `Router`, `Link`, and `Network` classes and create a small manually defined network.**
