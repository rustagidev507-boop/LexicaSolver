#pragma once

#include <lexica/graph/DependencyGraph.hpp>
#include <lexica/graph/SCCResult.hpp>

#include <lexica/planning/BlockResult.hpp>
#include <lexica/planning/BlockDependencyGraph.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Block Dependency Builder
    |--------------------------------------------------------------------------
    |
    | Constructs the dependency relationships between execution
    | blocks.
    |
    | Once the model has been decomposed into computational
    | blocks, this stage determines how those blocks depend on
    | one another and establishes the flow of execution across
    | the entire system.
    |
    | The resulting graph transforms a collection of independent
    | blocks into an executable model-wide dependency structure.
    |
    | This graph becomes the primary input for execution
    | planning and topological ordering.
    |
    | Typical Flow:
    |
    |     Dependency Graph
    |             +
    |         Block Result
    |             ↓
    |   Block Dependency Builder
    |             ↓
    |   Block Dependency Graph
    |             ↓
    |      Execution Order
    |
    | IMPORTANT:
    |
    | This component establishes inter-block relationships only.
    |
    | It does NOT determine execution order, classify blocks,
    | assign solvers, or perform numerical solving.
    |
    */

    class BlockDependencyBuilder
    {
    public:

        // Build dependencies between execution blocks.
        static BlockDependencyGraph build(
            const DependencyGraph& dependencyGraph,
            const SCCResult& sccResult,
            const BlockResult& blockResult);
    };
}