#pragma once

#include <vector>

#include <lexica/core/Types.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Strongly Connected Component
    |--------------------------------------------------------------------------
    |
    | Represents a group of variables that are mutually dependent
    | on one another within the dependency graph.
    |
    | Variables inside an SCC cannot be solved independently and
    | must be treated as a coupled subsystem during execution.
    |
    | SCCs form the basis of Lexica's block decomposition process
    | and allow the engine to identify feedback loops within a
    | model.
    |
    | Examples:
    |
    |     Pressure ↔ Density ↔ Temperature
    |
    |     FlowRate ↔ Velocity
    |
    | IMPORTANT:
    |
    | An SCC describes a structural relationship only.
    |
    | It does NOT contain equations, solver assignments, or
    | numerical results.
    |
    */

    struct SCC
    {
        // Variables belonging to this component.
        std::vector<VariableId>
            variables;
    };
}