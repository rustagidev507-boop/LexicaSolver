#pragma once

#include <vector>

#include <lexica/core/Types.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Dependency Graph
    |--------------------------------------------------------------------------
    |
    | Represents variable-level dependencies discovered after
    | structural matching.
    |
    | The dependency graph describes how the computation of one
    | variable relies on the availability of other variables,
    | exposing the flow of information throughout the model.
    |
    | This graph serves as the foundation for:
    |
    |     - Cycle Detection
    |     - SCC Discovery
    |     - Block Formation
    |     - Execution Planning
    |
    | Typical Flow:
    |
    |     Structural Matching
    |             ↓
    |     Dependency Graph
    |             ↓
    |     SCC Detection
    |             ↓
    |     Block Decomposition
    |
    | IMPORTANT:
    |
    | This graph captures dependency relationships only.
    |
    | It does NOT contain equations, numerical values,
    | execution order, or solver information.
    |
    */

    struct DependencyGraph
    {
        // Variable -> variables required to compute it.
        std::vector<
            std::vector<VariableId>
        > dependencies;
    };
}