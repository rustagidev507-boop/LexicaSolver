# Lexica

Lexica is an equation-oriented engineering computation engine designed to transform high-level design intent into solvable mathematical systems.

Instead of manually determining calculation order, dependency chains, and solving strategies, Lexica analyzes a system of equations, discovers structural relationships, decomposes coupled subsystems, plans execution, and computes the final solution automatically.

---

## Vision

Engineering problems are rarely a sequence of independent calculations.

A change in one variable often affects many others, creating tightly coupled systems of constraints.

The long-term goal of Lexica is to allow users to describe what they want to achieve while the engine determines:

- Which equations are relevant
- Which variables are known and unknown
- How the system is structurally connected
- Which variables depend on one another
- Which subsystems are coupled
- Which solving strategy should be applied
- How the complete system should be executed

In other words:

> User Intent → Mathematical Model → Structural Analysis → Execution Plan → Solution

---

## Current Architecture

The engine currently implements a complete equation-solving pipeline.

### 1. Model Construction

Engineering systems are represented using:

- Variables
- Mathematical Expressions
- Equations

These are assembled into a unified model representation.

### 2. Structural Analysis

The model is transformed into structural graphs that expose relationships between equations and variables.

This stage includes:

- Structural graph construction
- Equation-variable matching
- Dependency analysis
- Strongly connected component detection

### 3. Block Decomposition

Coupled regions of the system are automatically identified and grouped into computational blocks.

Each block represents a subsystem that can be solved independently.

### 4. Solver Planning

Blocks are analyzed and classified.

Appropriate solving strategies are selected based on block characteristics.

### 5. Numerical Execution

The execution layer currently supports:

- Direct computation blocks
- Newton-Raphson based nonlinear blocks

Residual evaluation, Jacobian generation, and linear system solving are performed automatically.

---

## Example Pipeline

```text
Variables + Equations
          │
          ▼
      Model
          │
          ▼
 Structural Analysis
          │
          ▼
 Dependency Graph
          │
          ▼
      SCC Detection
          │
          ▼
 Block Decomposition
          │
          ▼
 Solver Planning
          │
          ▼
 Numerical Execution
          │
          ▼
      Solution
```

---

## Project Structure

```text
include/
└── lexica/

src/

examples/

docs/

tests/
```

### Major Components

| Component | Responsibility |
|------------|---------------|
| Builder | Model construction |
| Expression | Mathematical expression representation |
| Analysis | Structural model analysis |
| Matching | Equation-variable assignment |
| Graph | Dependency discovery and SCC detection |
| Planning | Block formation and execution planning |
| Runtime | Residual and Jacobian evaluation |
| Solver | Numerical solving |
| Execute | Solver selection and execution |
| Result | Solver output representation |

---

## Current Capabilities

- Expression tree construction
- Equation-based modeling
- Structural graph generation
- Bipartite matching
- Dependency graph generation
- Tarjan SCC decomposition
- Computational block generation
- Block classification
- Solver planning
- Residual evaluation
- Jacobian generation
- Newton-Raphson solving
- End-to-end execution pipeline

---

## Long-Term Direction

Lexica is being designed as a foundation for autonomous engineering computation.

Future capabilities may include:

- Knowledge-based equation retrieval
- Intent-driven model generation
- Optimization workflows
- Multi-domain engineering systems
- Advanced nonlinear solvers
- Symbolic preprocessing
- Sparse matrix support
- Dynamic system simulation
- Design-space exploration

---

## Status

Active development.

The current focus is building a robust structural analysis and numerical execution engine before expanding into knowledge retrieval and intent-driven modeling.

---

## License

MIT License
