#pragma once

#include <vector>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Variable Vector
    |--------------------------------------------------------------------------
    |
    | Represents a collection of numerical variable values used
    | during model execution and solving.
    |
    | Variable vectors provide a compact representation of the
    | current state of a system and are passed between numerical
    | components throughout the execution pipeline.
    |
    | Typical Uses:
    |
    |     - Initial Guesses
    |     - Solver Updates
    |     - Intermediate States
    |     - Final Solutions
    |
    | Typical Flow:
    |
    |     Initial Guess
    |            ↓
    |       Solver
    |            ↓
    |    Variable Vector
    |            ↓
    |    Updated State
    |
    | IMPORTANT:
    |
    | This object stores numerical values only.
    |
    | It does NOT contain variable metadata, equations,
    | dependencies, or solver configuration.
    |
    */

    struct VariableVector
    {
        // Numerical values of model variables.
        std::vector<double>
            values;
    };
}