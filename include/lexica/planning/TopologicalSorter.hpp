#pragma once

#include <lexica/planning/ExecutionPlan.hpp>
#include <lexica/planning/BlockDependencyGraph.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Topological Sorter
    |--------------------------------------------------------------------------
    |
    | Determines a valid execution order for computational
    | blocks based on their dependency relationships.
    |
    | Once block dependencies have been established, this stage
    | transforms the dependency graph into an executable plan
    | that guarantees each block is processed only after all of
    | its prerequisites are available.
    |
    | The resulting execution plan represents the final output
    | of the structural planning pipeline and serves as the
    | primary input to the execution engine.
    |
    | Typical Flow:
    |
    |     Block Dependency Graph
    |               ↓
    |       Topological Sorter
    |               ↓
    |         Execution Plan
    |               ↓
    |         Solver Execution
    |
    | IMPORTANT:
    |
    | This component determines execution order only.
    |
    | It does NOT classify blocks, assign solvers, evaluate
    | equations, or perform numerical solving.
    |
    */

    class TopologicalSorter
    {
    public:

        // Generate an executable block ordering.
        static ExecutionPlan sort(
            const BlockDependencyGraph& graph);
    };
}