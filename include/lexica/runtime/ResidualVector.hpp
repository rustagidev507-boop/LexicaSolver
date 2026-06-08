#pragma once

#include <vector>

namespace lexica
{
    /*
    |--------------------------------------------------------------------------
    | Residual Vector
    |--------------------------------------------------------------------------
    |
    | Represents the numerical error of a system of equations at
    | a particular evaluation state.
    |
    | Each residual corresponds to an equation and indicates how
    | closely the current variable values satisfy the underlying
    | mathematical constraints.
    |
    | Residual vectors are a fundamental component of nonlinear
    | solving and are used to measure convergence throughout the
    | execution process.
    |
    | Typical Flow:
    |
    |     Model State
    |            ↓
    |    Residual Evaluator
    |            ↓
    |      Residual Vector
    |            ↓
    |      Newton Solver
    |
    | IMPORTANT:
    |
    | This object stores numerical residual values only.
    |
    | It does NOT contain equations, variables, Jacobians, or
    | solver state.
    |
    */

    struct ResidualVector
    {
        // Residual value for each equation.
        std::vector<double>
            values;
    };
}