#pragma once

#include <vector>

#include <lexica/core/Types.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Equation Information
    |--------------------------------------------------------------------------
    |
    | Captures structural information extracted from an equation
    | during the analysis phase.
    |
    | This object acts as an intermediate representation between
    | raw model equations and higher-level structural algorithms.
    |
    | The collected information is used by dependency analysis,
    | matching, graph construction, and execution planning.
    |
    | IMPORTANT:
    |
    | EquationInfo is derived data.
    |
    | It does not represent the equation itself, but rather the
    | structural properties discovered during analysis.
    |
    */

    struct EquationInfo
    {
        // Equation being analyzed.
        EquationId equation{};

        // Variables with available values.
        std::vector<VariableId> knownVariables;

        // Variables that still require solving.
        std::vector<VariableId> unknownVariables;

        // Number of unknown variables.
        std::size_t unknownCount{};
    };
}