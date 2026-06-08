#pragma once

#include <vector>

#include <lexica/core/Types.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Structural Block
    |--------------------------------------------------------------------------
    |
    | Represents an executable subsystem discovered during block
    | decomposition.
    |
    | A structural block groups equations and variables that must
    | be analyzed and solved together due to their dependency
    | relationships.
    |
    | Depending on the model structure, a block may represent:
    |
    |     - A direct calculation
    |     - A coupled algebraic loop
    |     - A larger nonlinear subsystem
    |
    | Structural blocks form the fundamental execution units of
    | the Lexica solving pipeline.
    |
    | IMPORTANT:
    |
    | This object describes the composition of a subsystem.
    |
    | It does NOT contain solver assignments, execution order,
    | numerical state, or convergence information.
    |
    */

    struct StructuralBlock
    {
        // Unique block identifier.
        std::size_t id{};

        // Variables belonging to this block.
        std::vector<VariableId>
            variables;

        // Equations belonging to this block.
        std::vector<EquationId>
            equations;
    };
}