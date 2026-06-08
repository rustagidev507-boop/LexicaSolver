#pragma once

#include <lexica/core/Model.hpp>

#include <lexica/graph/DependencyGraph.hpp>

#include <lexica/matching/MatchingResult.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Dependency Graph Builder
    |--------------------------------------------------------------------------
    |
    | Constructs the variable dependency graph of a model using
    | structural matching information.
    |
    | Once equations have been matched to variables, the builder
    | determines how variables depend on one another and exposes
    | the flow of information throughout the system.
    |
    | The resulting graph becomes the foundation for:
    |
    |     - Cycle Detection
    |     - SCC Discovery
    |     - Block Formation
    |     - Execution Planning
    |
    | Typical Flow:
    |
    |     Model + Matching
    |             ↓
    |     Dependency Graph Builder
    |             ↓
    |     Dependency Graph
    |             ↓
    |     SCC Detection
    |
    | IMPORTANT:
    |
    | This component discovers structural dependencies only.
    |
    | It does NOT perform cycle detection, block decomposition,
    | execution planning, or numerical solving.
    |
    */

    class DependencyGraphBuilder
    {
    public:

        // Build the dependency graph for a matched model.
        static DependencyGraph build(
            const Model& model,
            const MatchingResult& matching);
    };
}