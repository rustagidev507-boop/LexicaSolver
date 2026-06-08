#pragma once

#include <string>

#include "Types.hpp"

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Variable
    |--------------------------------------------------------------------------
    |
    | Represents a model-level quantity participating in one or
    | more mathematical relationships.
    |
    | Variables form the state of a model and are referenced by
    | equations throughout the Lexica pipeline.
    |
    | Examples:
    |
    |     Pressure
    |     Temperature
    |     MassFlow
    |     Velocity
    |
    | IMPORTANT:
    |
    | This object represents a variable instance within a model.
    |
    | It may contain values and execution state, but it does NOT
    | contain structural relationships, dependency information,
    | or solver-specific metadata.
    |
    */

    struct Variable
    {
        // Stable variable identifier.
        VariableId id{};

        // Human-readable variable name.
        std::string name;

        // Current numerical value.
        Scalar value{};

        // Current execution status.
        VariableStatus status
        {
            VariableStatus::Unknown
        };
    };
}