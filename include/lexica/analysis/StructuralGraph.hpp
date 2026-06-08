#pragma once

#include <vector>

#include <lexica/core/Types.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Structural Graph
    |--------------------------------------------------------------------------
    |
    | Simplified structural representation of a model used during
    | equation matching and dependency discovery.
    |
    | The structural graph captures which variables participate
    | in each equation while intentionally ignoring numerical
    | values and mathematical details.
    |
    | This abstraction allows structural algorithms to reason
    | about solvability and connectivity without performing
    | equation evaluation.
    |
    | Typical Uses:
    |
    |     - Equation Matching
    |     - Dependency Analysis
    |     - Cycle Detection
    |     - Block Formation
    |
    | IMPORTANT:
    |
    | This graph describes structure only.
    |
    | It does NOT contain dependency directions, execution order,
    | or numerical information.
    |
    */

    struct StructuralGraph
    {
        // Variables participating in each equation.
        std::vector<
            std::vector<VariableId>
        > equationVariables;
    };
}