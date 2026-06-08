#pragma once

#include <vector>

#include <lexica/core/Types.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Incidence Graph
    |--------------------------------------------------------------------------
    |
    | Structural representation of the relationship between
    | equations and variables within a model.
    |
    | The incidence graph serves as the foundation for Lexica's
    | structural analysis pipeline and provides a compact view of
    | how variables participate in equations.
    |
    | This representation is used by:
    |
    |     - Structural Analysis
    |     - Equation Matching
    |     - Dependency Discovery
    |     - Block Decomposition
    |     - Execution Planning
    |
    | IMPORTANT:
    |
    | The incidence graph describes connectivity only.
    |
    | It does NOT contain:
    |
    |     - Numerical values
    |     - Dependency directions
    |     - Solver information
    |     - Execution metadata
    |
    | Those are derived during later stages of the pipeline.
    |
    */

    struct IncidenceGraph
    {
        // Variables participating in each equation.
        std::vector<
            std::vector<VariableId>
        > equationVariables;

        // Equations referencing each variable.
        std::vector<
            std::vector<EquationId>
        > variableEquations;
    };
}