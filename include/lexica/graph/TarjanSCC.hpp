#pragma once

#include <stack>
#include <vector>

#include <lexica/graph/DependencyGraph.hpp>
#include <lexica/graph/SCCResult.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Tarjan SCC
    |--------------------------------------------------------------------------
    |
    | Identifies strongly connected components within a dependency
    | graph using Tarjan's algorithm.
    |
    | This stage is responsible for detecting feedback loops and
    | mutually dependent variable groups that cannot be solved
    | independently.
    |
    | The discovered components form the foundation of block
    | decomposition and allow Lexica to transform a large
    | interconnected system into smaller solvable subsystems.
    |
    | Typical Flow:
    |
    |     Dependency Graph
    |             ↓
    |         Tarjan SCC
    |             ↓
    |     Strongly Connected Components
    |             ↓
    |       Block Formation
    |
    | IMPORTANT:
    |
    | This component performs structural decomposition only.
    |
    | It does NOT classify blocks, assign solvers, generate
    | execution plans, or perform numerical solving.
    |
    */

    class TarjanSCC
    {
    public:

        // Discover strongly connected components.
        static SCCResult find(
            const DependencyGraph& graph);

    private:

        // Recursive Tarjan traversal.
        static void strongConnect(
            VariableId variable,
            const DependencyGraph& graph,
            SCCResult& result,
            std::vector<int>& indices,
            std::vector<int>& lowLinks,
            std::vector<bool>& onStack,
            std::stack<VariableId>& stack,
            int& currentIndex);
    };
}