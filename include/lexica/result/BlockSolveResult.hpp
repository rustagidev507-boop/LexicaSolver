#pragma once

#include <lexica/runtime/VariableVector.hpp>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Block Solve Result
    |--------------------------------------------------------------------------
    |
    | Represents the outcome of solving a computational block.
    |
    | During execution, each block is processed by its assigned
    | numerical solver and produces a result describing whether
    | the solve was successful along with the computed variable
    | values.
    |
    | This structure provides a common interface between the
    | execution engine and individual solver implementations.
    |
    | Typical Flow:
    |
    |     Structural Block
    |             ↓
    |          Solver
    |             ↓
    |     Block Solve Result
    |             ↓
    |     Model Execution
    |
    | IMPORTANT:
    |
    | This object represents the result of a single block solve.
    |
    | It does NOT contain execution plans, solver selection
    | information, or model-wide state.
    |
    */

    struct BlockSolveResult
    {
        // Computed variable values.
        VariableVector solution;

        // Indicates whether the solve succeeded.
        bool success = false;
    };
}